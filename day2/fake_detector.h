#pragma once

#include "armor_detector.h"
#include <random>

class FakeDetector : public ArmorDetector
{
    public:
        //实现init:打印配置信息
        bool init(const DetectorConfig& config) override
        {
            threshold_value_=config.threshold;
            std::cout << "FakeDetector init,threshold ="
                      << threshold_value_ << std::endl;
            return true;
        }
        
        //实现process:生成3个随机位置的装甲版
        std::vector<ArmorBox> process(const cv::Mat& frame) override
        {
            image_size_ = frame.size();
            std::vector<ArmorBox> boxes;
            std::mt19937 gen(42);
            std::uniform_int_distribution<int> x(0,image_size_.width - 100);
            std::uniform_int_distribution<int> y(0,image_size_.height - 100);

            for (int i=0;i<3;i++)
            {
                ArmorBox box;
                box.bbox = cv::Rect(x(gen),y(gen),120,60);
                box.center = cv::Point2f(box.bbox.x + box.bbox.width/2,
                                         box.bbox.y + box.bbox.height/2);
                box.id = i+1;
                box.confidence = 0.9f;
                boxes.push_back(box);
            }
            return boxes;
        }

        //实现drawResult:在图像上画框
        void drawResult(cv::Mat& frame,
                        const std::vector<ArmorBox>& boxes) override
        {
            for(const auto& box : boxes)
            {
                cv::rectangle(frame,box.bbox,cv::Scalar(0,0,255),2);
                cv::putText(frame,"ID:" + std::to_string(box.id),
                            box.bbox.tl() + cv::Point(0,-8),
                            cv::FONT_HERSHEY_SIMPLEX,0.7,
                            cv::Scalar(0,255,0),2);
            }
        }

};