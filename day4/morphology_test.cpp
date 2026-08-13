#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    if(argc < 2)
    {
        cerr << "用法：./morphology_test <图片路径>" << endl;
        return -1;
    }

    Mat img = imread(argv[1],IMREAD_COLOR);
    if(img.empty()) return -1;

    Mat hsv;
    cvtColor(img,hsv,COLOR_BGR2HSV);
    Mat mask1,mask2,mask;
    inRange(hsv,Scalar(0,80,80),Scalar(10,255,255),mask1);
    inRange(hsv,Scalar(160,80,80),Scalar(180,255,255),mask2);
    bitwise_or(mask1,mask2,mask);

    Mat kernel=getStructuringElement(MORPH_RECT,Size(5,5));

    Mat eroded,dilated,opened,closed;
    erode(mask,eroded,kernel);
    dilate(mask,dilated,kernel);
    morphologyEx(mask,opened,MORPH_OPEN,kernel);
    morphologyEx(mask,closed,MORPH_CLOSE,kernel);

    Mat r1,r2,r3,all;
    hconcat(mask,eroded,r1);
    hconcat(dilated,opened,r2);
    hconcat(closed,Mat(),r3);
    vconcat(r1,r2,all);
    vconcat(all,r3,all);

    imshow("二值 | 腐蚀 | 膨胀",all);
    imshow("开运算",opened);
    imshow("闭运算",closed);
    waitKey(0);

    imwrite("morphology_result.png",all);
    cout << "结果已保存 morphology_result.png" << endl;
    return 0;
}