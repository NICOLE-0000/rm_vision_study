#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    //1.创建 640✖480 的黑色图像
    Mat image(480,640,CV_8UC3,Scalar(0,0,0));

    //2.用ptr 遍历：把整张图设为纯绿色
    for (int r=0;r<image.rows;r++)
    {
        Vec3b* ptr = image.ptr<Vec3b>(r);
        for(int c=0;c<image.cols;c++)
        {
            ptr[c][0]=0;
            ptr[c][1]=255;
            ptr[c][2]=0;
        }      
    }

    //3.在图像中央画一个红色园
    for(int r=200;r<280;r++)
    {
        for(int c=280;c<360;c++)
        {
            image.at<Vec3b>(r,c)=Vec3b(0,0,255);
        }
    }

    //4.打印图像前3个元素和图像中间的值
    cout << "" << image.type() << endl;
    cout << "左上角像素（B，G，R）" 
         << (int)image.at<Vec3b>(0,0)[0] << ""
         << (int)image.at<Vec3b>(0,0)[1] << ""
         << (int)image.at<Vec3b>(0,0)[2] << endl;
    cout << "中心像素（B，G，R）" 
         << (int)image.at<Vec3b>(240,320)[0] << ""
         << (int)image.at<Vec3b>(240,320)[1] << ""
         << (int)image.at<Vec3b>(240,320)[2] << endl;

    //5.显示并保存
    imshow("Green Image",image);
    imwrite("green_image.png",image);
    waitKey(0);

    return 0;

}