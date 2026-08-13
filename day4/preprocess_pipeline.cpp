#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) 
{
    if (argc < 2) 
    {
        cerr << "用法: ./preprocess_pipeline <图片路径>" << endl;
        return -1;
    }

    Mat frame = imread(argv[1], IMREAD_COLOR);
    if (frame.empty()) return -1;

    // ============ RM 标准预处理流水线 ============

    // 1. 转 HSV
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    // 2. inRange 二值化（红色，两段合并）
    Mat m1, m2, mask;
    inRange(hsv, Scalar(0, 80, 80), Scalar(10, 255, 255), m1);
    inRange(hsv, Scalar(160, 80, 80), Scalar(180, 255, 255), m2);
    bitwise_or(m1, m2, mask);

    // 3. 开运算去噪（先腐蚀后膨胀，去掉小白点噪点）
    Mat opened;
    Mat kernel_open = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(mask, opened, MORPH_OPEN, kernel_open);

    // 4. 闭运算连断裂（先膨胀后腐蚀，填空洞、连断裂灯条）
    Mat closed;
    Mat kernel_close = getStructuringElement(MORPH_RECT, Size(7, 7));
    morphologyEx(opened, closed, MORPH_CLOSE, kernel_close);

    // 5. Canny 边缘检测（在形态学处理后的图上提取边缘）
    Mat edges;
    Canny(closed, edges, 30, 90);

    // 6. 并排显示每一阶段的结果
    Mat r1, r2, all;
    hconcat(mask, opened, r1);
    hconcat(closed, edges, r2);
    vconcat(r1, r2, all);

    imshow("二值 | 开运算", r1);
    imshow("闭运算 | Canny边缘", r2);
    waitKey(0);

    imwrite("pipeline_result.png", all);
    cout << "流水线结果已保存 pipeline_result.png" << endl;

    return 0;
}