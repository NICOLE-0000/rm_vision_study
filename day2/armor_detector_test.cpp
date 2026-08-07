#include<iostream>
#include<opencv2/opencv.hpp>
#include"fake_detector.h"

using namespace std;
using namespace cv;

int main()
{
    //1.创建一个 640x480 黑色画布，模拟一帧图像
    Mat frame(480,640,CV_8UC3,Scalar(30,30,30));

    //2.多态
    ArmorDetector* detector = new FakeDetector();

    //3。初始化
    DetectorConfig config;
    config.config_path = "config.yaml";
    config.threshold = 150;
    config.debug_draw = true;
    detector -> init(config);

    //4.处理一帧
    vector<ArmorBox> boxes = detector -> process(frame);
    cout << "检测到" << boxes.size() << "个装甲板" << endl;

    //5.打印每个装甲板的中心坐标
    for (const auto& box : boxes)
    {
        cout << "ID=" << box.id
             << "中心=(" << box.center.x << ","
             << box.center.y << ")" << endl;
    }

    //6.绘制并显示
    detector -> drawResult(frame,boxes);
    imshow("Fake Detection",frame);
    waitKey(0);

    //7.释放内存
    delete detector;
    return 0;
}