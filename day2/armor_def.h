#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

//装甲板框结构
struct ArmorBox
{
    cv::Rect bbox;           //装甲板的矩形框
    cv::Point2f center;     //装甲板中心
    int id = -1;            //数字ID，-1表示未识别
    float confidence = 0.0f;//置信度 0-1
    bool is_large = false;  //true=大装甲板，false=小装甲板
};

//检测器配置结构
struct DetectorConfig
{
    std::string config_path;    //配置文件路径
    int threshold = 100;        //默认阙值
    bool debug_draw = true;     //是否绘制调试信息
};