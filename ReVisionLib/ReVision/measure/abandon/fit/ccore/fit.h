#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include "../ifit.h"

class Fit : public IFit
{
public:
    virtual void fitLine(std::vector<cv::Point2f>& points, double& k, double& b) override;
    virtual void fitLine(std::vector<cv::Point2d>& points, double& k, double& b) override;

    virtual void fitCircle(std::vector<cv::Point2f>& points, cv::Point2d& center, double& radius) override;
    virtual void fitCircle(std::vector<cv::Point2d>& points, cv::Point2d& center, double& radius) override;

private:
    template<typename _Tp> void fitLineBase(const std::vector<cv::Point_<_Tp>>& points, double& k, double& b);
    template<typename _Tp> void fitCircleBase(const std::vector<cv::Point_<_Tp>>& points, cv::Point2d& center, double& radius);

};
