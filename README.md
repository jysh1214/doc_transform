# DOC TRANSFORM

It's inspired by [Four-Point-Invoice-Transform-with-OpenCV](https://github.com/KMKnation/Four-Point-Invoice-Transform-with-OpenCV). I change some code to enhance white zone and decrease noise effect.

## env
- any c++ compiler (we use clang in this project)
- opencv

## compiler & use
```
make
./transform <YOUR_IMAGE>
```

## result
<Table>
    <tr>
        <th>Input Image</th>
        <th>Output Image</th>
    </tr>
    <tr>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/1.jpg" alt="Original" width="400" height="500" align="middle"/></td>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/1_output.png" alt="Original" width="400" height="500" align="middle"/></td>
    </tr>
    <tr>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/2.jpg" alt="Original" width="400" height="500" align="middle"/></td></th>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/2_output.png" alt="Original" width="400" height="500" align="middle"/></td>
    </tr>
    <tr>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/3.jpg" alt="Original" width="400" height="500" align="middle"/></td></th>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/3_output.png" alt="Original" width="400" height="500" align="middle"/></td>
    </tr>
    <tr>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/4.jpg" alt="Original" width="400" height="500" align="middle"/></td>
        <td><img src="https://github.com/jysh1214/doc_transform/blob/main/asset/4_output.png" alt="Original" width="400" height="500" align="middle"/></td>
    </tr>
</Table>
