#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "用法: ./video_hsv <视频路径>" << endl;
        return -1;
    }

    // 打开视频
    VideoCapture cap(argv[1]);
    if (!cap.isOpened()) {
        cerr << "视频打开失败" << endl;
        return -1;
    }

    // 视频信息
    cout << "视频宽度: " << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "视频高度: " << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "视频帧率: " << cap.get(CAP_PROP_FPS) << endl;

    Mat frame, hsv, mask_red, mask_blue, result;

    // 帧率统计变量
    double t_start, t_end;
    int fps_count = 0;
    double fps = 0;

    while (true) {
        t_start = (double)getTickCount();   // 计时开始

        // 1. 读一帧
        cap >> frame;
        if (frame.empty()) break;   // 视频结束

        // 2. 转 HSV
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // 3. 红色提取（两段合并）
        Mat m1, m2;
        inRange(hsv, Scalar(0,   80, 80), Scalar(10,  255, 255), m1);
        inRange(hsv, Scalar(160, 80, 80), Scalar(180, 255, 255), m2);
        bitwise_or(m1, m2, mask_red);

        // 4. 蓝色提取（单段）
        inRange(hsv, Scalar(100, 80, 80), Scalar(124, 255, 255), mask_blue);

        // 5. 把两色拼在一起显示（红在左，蓝在右）
        hconcat(mask_red, mask_blue, result);

        // 6. 统计帧率
        fps_count++;
        t_end = (double)getTickCount();
        double elapsed = (t_end - t_start) / getTickFrequency();  // 秒
        fps = 1.0 / elapsed;   // 帧率 = 1/处理一帧的时间

        // 7. 在帧上叠加信息
        putText(result, "FPS: " + to_string((int)fps),
                Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
                Scalar(255, 255, 255), 2);

        // 8. 显示
        imshow("Red | Blue", result);

        // 9. 按键处理
        int key = waitKey(1);
        if (key == 'q' || key == 27) break;
    }

    cap.release();
    return 0;
}