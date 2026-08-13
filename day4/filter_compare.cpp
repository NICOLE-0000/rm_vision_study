#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    if(argc < 2)
    {
        cerr << "用法：./filter_compare <图片路径>" << endl;
        return -1;
    }

    Mat img = imread(argv[1],IMREAD_COLOR);
    if(img.empty()) return -1;

    Mat gray;
    cvtColor(img,gray,COLOR_BGR2GRAY);

    Mat blur_out,gauss_out,median_out;
    blur(gray,blur_out,Size(5,5));
    GaussianBlur(gray,gauss_out,Size(5,5),0);
    medianBlur(gray,median_out,5);

    Mat row1,row2,all;
    hconcat(gray,blur_out,row1);
    hconcat(gauss_out,median_out,row2);
    vconcat(row1,row2,all);

    imshow("原图 | 均值 | 高斯 | 中值",all);
    waitKey(0);

    imwrite("filter_compare.png",all);
    cout << "对比图已保存 filter_compare.png" << endl;

    return 0;

}