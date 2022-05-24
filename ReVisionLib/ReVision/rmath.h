#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

namespace rv
{
#ifdef CV_PI
#define RV_PI CV_PI
#else
#define RV_PI (3.1415926535897932384626433832795)
#endif

    template<typename _Tp>
    constexpr inline bool fuzzyCompare(_Tp p1, _Tp p2) noexcept
    {
        return p1 == p2;
    }

    template<> inline bool fuzzyCompare(double p1, double p2) noexcept
    {
        return std::abs(p1 - p2) <= 1.0E-07;
    }

    template<> inline bool fuzzyCompare(float p1, float p2) noexcept
    {
        return std::abs(p1 - p2) <= 1.0E-05f;
    }

    constexpr inline bool isNull(double d) noexcept
    {
        return d == 0.0;
    }

    //弧度转角度
    template<typename _Tp>
    inline double rad2deg(_Tp rad)
    {
        return double(rad) * 180.0 / CV_PI;
    }

    inline float rad2deg(float rad)
    {
        return float(rad * 180.0f / CV_PI);
    }

    //角度转弧度
    template<typename _Tp>
    inline double deg2rad(_Tp deg)
    {
        return double(deg) * CV_PI / 180.0;
    }

    inline float deg2rad(float deg)
    {
        return float(deg * CV_PI / 180);
    }

    //点位绕点旋转
    template<typename _Tp>
    inline cv::Point_<_Tp> rotatePoint(const cv::Point_<_Tp>& center, const cv::Point_<_Tp>& p, double radian)
    {
        _Tp p2x = _Tp((p.x - center.x) * std::cos(radian) - (p.y - center.y) * std::sin(radian) + center.x);
        _Tp p2y = _Tp((p.x - center.x) * std::sin(radian) + (p.y - center.y) * std::cos(radian) + center.y);

        return cv::Point_<_Tp>(p2x, p2y);
    }

    //点位绕点旋转
    template<typename _Tp>
    inline void rotatePoint(_Tp cx, _Tp cy, _Tp p1x, _Tp p1y, double radian, _Tp& p2x, _Tp& p2y)
    {
        p2x = _Tp((p1x - cx) * std::cos(radian) - (p1y - cy) * std::sin(radian) + cx);
        p2y = _Tp((p1x - cx) * std::sin(radian) + (p1y - cy) * std::cos(radian) + cy);
    }

}
