#include <iostream>     // 输入输出流头文件
#include <opencv2/opencv.hpp>  // OpenCV 头文件

// 使用标准的命名空间
using namespace std;
using namespace cv;

int main() {
    // 1. 在终端打印一句话
    cout << "Hello RoboMaster!" << endl;
    cout << "OpenCV version: " << CV_VERSION << endl;

    // 2. 创建一个 640x480 的纯黑色图像
    Mat image(480, 640, CV_8UC3, Scalar(0, 0, 0));

    // 3. 在图像中央画一个红色的圆
    circle(image, Point(320, 240), 100, Scalar(0, 0, 255), -1);

    // 4. 写上文字
    putText(image, "RM Vision Day 1", Point(180, 400),
            FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 255, 255), 2);

    // 5. 显示图像
    imshow("Hello RM", image);
    waitKey(0);  // 等待按键

    // 6. 保存图像到文件
    imwrite("hello_rm.png", image);
    cout << "Image saved as hello_rm.png" << endl;

    return 0;
}

  