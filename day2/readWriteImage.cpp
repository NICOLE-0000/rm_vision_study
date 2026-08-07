#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
    //1.从命令行读取图片路径
    //  运行方式：./readWriteImage test.png
    if (argc<2)
    {
        cerr << "用法：./readWriteImage <图片路径>" << endl;
        return -1;
    }

    //2.读图（IMREAD_COLOR表示按彩色读入）
    Mat img =  imread(argv[1],IMREAD_COLOR);
    if(img.empty())
    {
        cerr << "图片读取失败！请检查路径:" << argv[1] << endl;
        return -1;
    }

    //3.打印图像信息
    cout << "图像宽:" << img.cols << endl;
    cout << "图像高" << img.rows << endl;
    cout << "通道数" << img.channels() << endl;
    cout << "类型" << img.type() << endl;
    cout << "一个像素字节数" << img.elemSize() << endl;
    cout << "一行字节数" << img.step << endl; 

    //4.像素取反
    Mat inverted = Mat(img.size(),img.type());
    for(int r=0;r<img.rows;r++)
    {
        const uchar* src_ptr = img.ptr<uchar>(r);
        uchar* dst_ptr = inverted.ptr<uchar>(r);
        for(int c=0; c<img.cols*img.channels() ; c++)
        {
            dst_ptr[c] = 255 - src_ptr[c];
        }
    }

    //5.保存
    imwrite("inverted.png",inverted);
    cout << "取反图已保存为 inverted.png" << endl;

    //6.显示对比
    namedWindow("Original",WINDOW_NORMAL);
    namedWindow("Inverted",WINDOW_NORMAL);
    imshow("Original",img);
    imshow("Inverted",inverted);
    waitKey(0); 

    return 0;
}