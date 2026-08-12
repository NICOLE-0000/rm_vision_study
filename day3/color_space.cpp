#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "用法: ./color_space <图片路径>" << endl;
        return -1;
    }

    Mat bgr = imread(argv[1], IMREAD_COLOR);
    if (bgr.empty()) {
        cerr << "图片读取失败" << endl;
        return -1;
    }

    // 转换到不同色彩空间
    Mat gray, hsv, lab;
    cvtColor(bgr, gray, COLOR_BGR2GRAY);
    cvtColor(bgr, hsv,  COLOR_BGR2HSV);
    cvtColor(bgr, lab,  COLOR_BGR2Lab);

    // 并排显示四个窗口
    imshow("BGR", bgr);
    imshow("Gray", gray);
    imshow("HSV", hsv);
    imshow("Lab", lab);
    waitKey(0);

    // 打印同一个像素点在四种空间下的数值
    // 选中心像素
    Point center(bgr.cols / 2, bgr.rows / 2);
    cout << "中心像素 (" << center.x << ", " << center.y << ") 数值:" << endl;
    cout << "  BGR: " << (int)bgr.at<Vec3b>(center)[0] << " "
         << (int)bgr.at<Vec3b>(center)[1] << " "
         << (int)bgr.at<Vec3b>(center)[2] << endl;
    cout << "  HSV: " << (int)hsv.at<Vec3b>(center)[0] << " "
         << (int)hsv.at<Vec3b>(center)[1] << " "
         << (int)hsv.at<Vec3b>(center)[2] << endl;
    cout << "  Lab: " << (int)lab.at<Vec3b>(center)[0] << " "
         << (int)lab.at<Vec3b>(center)[1] << " "
         << (int)lab.at<Vec3b>(center)[2] << endl;

    return 0;
}