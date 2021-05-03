#include "transform.hpp"

int main(int argc, char** argv)
{
    if (argc < 2) {
        return -1;
    }

    cv::Mat src, fix;
    src = cv::imread(argv[1]);
    if (src.empty()) {
        return -1;
    }

    transform(src, 0.4, fix);
    cv::imwrite("output.png", fix);

    return 0;
}
