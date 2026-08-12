#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std;
using namespace cv;

// 手写 inRange：遍历每个像素，检查是否在范围内
void manualInRange(const Mat& hsv, const Scalar& low, const Scalar& high, Mat& mask) {
    mask = Mat::zeros(hsv.size(), CV_8UC1);   // 全黑输出
    for (int r = 0; r < hsv.rows; r++) {
        const uchar* src = hsv.ptr<uchar>(r);
        uchar* dst = mask.ptr<uchar>(r);
        for (int c = 0; c < hsv.cols; c++) {
            // 取 H, S, V 三个通道
            uchar H = src[c * 3 + 0];
            uchar S = src[c * 3 + 1];
            uchar V = src[c * 3 + 2];
            // 判断是否在 [low, high] 范围内
            if (H >= low[0] && H <= high[0] &&
                S >= low[1] && S <= high[1] &&
                V >= low[2] && V <= high[2]) {
                dst[c] = 255;   // 满足条件 → 白
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) return -1;
    Mat img = imread(argv[1], IMREAD_COLOR);
    if (img.empty()) return -1;

    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);

    Scalar low(0, 50, 50);      // 先用红色阈值
    Scalar high(10, 255, 255);

    // 用 OpenCV 自带 inRange
    Mat mask_api, mask_manual;
    auto t1 = chrono::high_resolution_clock::now();
    inRange(hsv, low, high, mask_api);
    auto t2 = chrono::high_resolution_clock::now();

    // 用自己写的
    auto t3 = chrono::high_resolution_clock::now();
    manualInRange(hsv, low, high, mask_manual);
    auto t4 = chrono::high_resolution_clock::now();

    // 计算耗时（毫秒）
    double t_api = chrono::duration<double, milli>(t2 - t1).count();
    double t_manual = chrono::duration<double, milli>(t4 - t3).count();
    cout << "OpenCV inRange:   " << t_api    << " ms" << endl;
    cout << "手动 inRange:     " << t_manual << " ms" << endl;
    cout << "慢的倍数:         " << t_manual / t_api << " 倍" << endl;

    // 验证两种结果是否一致
    Mat diff = mask_api != mask_manual;
    int diff_count = countNonZero(diff);
    cout << "结果不一致的像素数: " << diff_count << " (应为 0)" << endl;

    imshow("API", mask_api);
    imshow("Manual", mask_manual);
    waitKey(0);
    return 0;
}
