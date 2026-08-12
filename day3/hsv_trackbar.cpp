#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 全局变量：trackbar 的值
int h_min = 0, h_max = 179;
int s_min = 0, s_max = 255;
int v_min = 0, v_max = 255;

Mat src, hsv, mask;

// trackbar 回调函数（拖动滑块时自动调用）
void onTrackbar(int, void*) {
    // 根据当前滑块值做二值化
    inRange(hsv,
            Scalar(h_min, s_min, v_min),
            Scalar(h_max, s_max, v_max),
            mask);
    imshow("Mask", mask);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "用法: ./hsv_trackbar <图片路径>" << endl;
        return -1;
    }

    src = imread(argv[1], IMREAD_COLOR);
    if (src.empty()) {
        cerr << "图片读取失败" << endl;
        return -1;
    }

    // 转换到 HSV
    cvtColor(src, hsv, COLOR_BGR2HSV);

    // 创建两个窗口
    namedWindow("Source", WINDOW_NORMAL);
    namedWindow("Mask", WINDOW_NORMAL);

    // 创建 6 个 trackbar
    createTrackbar("H min", "Mask", &h_min, 179, onTrackbar);
    createTrackbar("H max", "Mask", &h_max, 179, onTrackbar);
    createTrackbar("S min", "Mask", &s_min, 255, onTrackbar);
    createTrackbar("S max", "Mask", &s_max, 255, onTrackbar);
    createTrackbar("V min", "Mask", &v_min, 255, onTrackbar);
    createTrackbar("V max", "Mask", &v_max, 255, onTrackbar);

    // 显示原图
    imshow("Source", src);
    onTrackbar(0, nullptr);   // 先执行一次，显示初始结果

    // 鼠标回调：点击图像时，打印该像素的 BGR 和 HSV 值
    setMouseCallback("Source", [](int event, int x, int y, int, void*) {
        if (event != EVENT_LBUTTONDOWN) return;
        Vec3b bgr_val = src.at<Vec3b>(y, x);
        Vec3b hsv_val = hsv.at<Vec3b>(y, x);
        cout << "(" << x << ", " << y << ")  "
             << "BGR=(" << (int)bgr_val[0] << ","
             << (int)bgr_val[1] << ","
             << (int)bgr_val[2] << ")  "
             << "HSV=(" << (int)hsv_val[0] << ","
             << (int)hsv_val[1] << ","
             << (int)hsv_val[2] << ")" << endl;
    });

    cout << "操作指南:" << endl;
    cout << "  拖动 Mask 窗口的 6 个滑块调阈值" << endl;
    cout << "  左键点击 Source 窗口图像，打印该点 HSV" << endl;
    cout << "  按 q 退出" << endl;

    while (true) {
        int key = waitKey(30);
        if (key == 'q' || key == 27) break;   // q 或 ESC 退出
    }

    return 0;
}