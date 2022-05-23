#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class IFit
{
public:
    virtual void fitLine(std::vector<cv::Point2f>& points, double& k, double& b) = 0;
    virtual void fitLine(std::vector<cv::Point2d>& points, double& k, double& b) = 0;

    virtual void fitCircle(std::vector<cv::Point2f>& points, cv::Point2d& center, double& radius) = 0;
    virtual void fitCircle(std::vector<cv::Point2d>& points, cv::Point2d& center, double& radius) = 0;

    static cv::Ptr<IFit> create(bool useHCore = true);

};
