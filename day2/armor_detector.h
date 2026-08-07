#pragma once

#include "armor_def.h"

class ArmorDetector
{
    public:
        virtual ~ArmorDetector() = default; //虚析构函数
        //初始化：读取配置文件，设置参数
        virtual bool init(const DetectorConfig& config) = 0;
        //输入一帧图像，输出检测到的装甲板列表
        virtual std::vector<ArmorBox> process(const cv::Mat& frame) = 0;
        //在图像上画出检测结果
        virtual void drawResult(cv::Mat& frame,
                                const std::vector<ArmorBox>& boxes) = 0;

    protected:
        int threshold_value_ = 100;
        cv::Size image_size_;
};