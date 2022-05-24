#pragma once

#include <opencv2/opencv.hpp>

#ifdef ENABLE_HCORE
#include <HalconCpp.h>
using HMat = HalconCpp::HImage;
using HRegion = HalconCpp::HRegion;
#else
class HMat : public cv::Mat
{
public:
    HMat() : cv::Mat() {}
    HMat(const cv::Mat& mat) : cv::Mat(mat) {}
    HMat& operator = (const cv::Mat& mat) { *this = HMat(mat); return *this; }
};
#endif
