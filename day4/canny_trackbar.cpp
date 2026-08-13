#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat gray,edges;
int low_threshold = 50,high_threshold = 150;

void onTrackbar(int,void*)
{
    Canny(gray,edges,low_threshold,high_threshold);
    imshow("Canny",edges);
    imshow("原图",gray);
}

    int main(int argc,char** argv)
    {
         if (argc < 2) 
         {
            cerr << "用法: ./canny_trackbar <图片路径>" << endl;
            return -1;
        }

        Mat img = imread(argv[1], IMREAD_COLOR);
        if (img.empty()) return -1;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        namedWindow("Canny", WINDOW_NORMAL);
    createTrackbar("Low", "Canny", &low_threshold, 255, onTrackbar);
    createTrackbar("High", "Canny", &high_threshold, 255, onTrackbar);

    onTrackbar(0, nullptr);
    cout << "拖动滑块调 Canny 阈值, 按 q 退出" << endl;

    while (true) {
        int key = waitKey(30);
        if (key == 'q' || key == 27) break;
    }
    return 0;
    }

