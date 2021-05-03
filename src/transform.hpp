#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <math.h>
#include <iostream>

inline
float dist(const cv::Point p1, const cv::Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareContourAreas(const std::vector<cv::Point>& v1, const std::vector<cv::Point>& v2)
{
    double a = fabs(cv::contourArea(cv::Mat(v1)));
    double b = fabs(cv::contourArea(cv::Mat(v2)));

    return a > b;
}

static
void transform(const cv::Mat& src, const float threshold, cv::Mat& dst)
{
    assert(src.type() == CV_8UC3);

    float size = src.rows * src.cols;

    cv::Mat hsv, bin;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    // to enhance white zone
    cv::inRange(hsv, cv::Scalar(0, 0, 100), cv::Scalar(360, 50, 255), bin);

    cv::Mat ele = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(11, 11));
    cv::erode(bin, bin, ele);

    cv::Mat new_one;
    cv::bilateralFilter(bin, new_one, 11, 17, 17); // 11 or 5
    cv::medianBlur(new_one, new_one, 5);
    cv::Canny(new_one, new_one, 30, 400);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(new_one, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    std::sort(contours.begin(), contours.end(), compareContourAreas);

    // to find largest countours
    bool foundRectangle = false;
    std::vector<cv::Point> approx;
    cv::Point2f src_points[4];

    auto c = contours[0];
    double l = cv::arcLength(c, true);
    cv::approxPolyDP(c, approx, 0.02 * l, true);
    if (approx.size() == 4 && cv::contourArea(c) >= size * threshold) {
        src_points[0] = approx[0]; // 2
        src_points[1] = approx[1]; // 0
        src_points[2] = approx[2]; // 1
        src_points[3] = approx[3]; // 3
        foundRectangle = true;
    }

    if (!foundRectangle) {
        std::cout << " There is no valid rectangle found. Use origin picture." << "\n";
        dst = src.clone();
        return;
    }

    // find dst size
    float dsit_01 = dist(approx[0], approx[1]);
    float dsit_23 = dist(approx[2], approx[3]);
    float maxWidth = (dsit_01 > dsit_23)? dsit_01: dsit_23;

    float dsit_02 = dist(approx[0], approx[2]);
    float dsit_13 = dist(approx[1], approx[3]);
    float maxHeight = (dsit_02 > dsit_13)? dsit_02: dsit_13;

    cv::Point2f dst_points[4];
    dst_points[0] = cv::Point(maxWidth - 1, 0);
    dst_points[1] = cv::Point(0, 0);
    dst_points[2] = cv::Point(0, maxHeight - 1);
    dst_points[3] = cv::Point(maxWidth - 1, maxHeight - 1);

    cv::Mat transform_matrix = cv::getPerspectiveTransform(src_points, dst_points);
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	cv::warpPerspective(gray, dst, transform_matrix, cv::Size(maxWidth, maxHeight), cv::INTER_LINEAR);
}

#endif
