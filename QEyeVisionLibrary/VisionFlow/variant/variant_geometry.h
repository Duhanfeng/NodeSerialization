#pragma once

#include <ReVisionLib/ReVision.hpp>

namespace qv
{
    //复合几何,支持点,线,位姿,圆以及旋转矩形的复合
    class GeometryComplex
    {
    public:
        //构造
        GeometryComplex() noexcept;
        template<typename _Tp> GeometryComplex(const rv::Point<_Tp>& value) noexcept;
        template<typename _Tp> GeometryComplex(const rv::Line<_Tp>& value) noexcept;
        template<typename _Tp> GeometryComplex(const rv::Pose<_Tp>& value) noexcept;
        template<typename _Tp> GeometryComplex(const rv::Circle<_Tp>& value) noexcept;
        template<typename _Tp> GeometryComplex(const rv::RotatedRect<_Tp>& value) noexcept;

        //判断
        bool supportPoint() const;
        bool supportPoint2() const;
        bool supportAngle() const;
        bool supportSize() const;
        bool supportPose() const;

        //读取(不进行数据有效性校验)
        rv::Point<double> getPoint() const;
        rv::Point<double> getPoint2() const;
        double getAngle() const;
        double getWidth() const;
        double getHeight() const;
        rv::Size<double> getSize() const;

        rv::Line<double> getLine() const;
        rv::Pose<double> getPose() const;
        rv::Circle<double> getCircle() const;
        rv::RotatedRect<double> getRect() const;

        //读取(进行数据有效性校验)
        template<typename _Tp> bool tryGetPoint(rv::Point<_Tp>& value) const;
        template<typename _Tp> bool tryGetPoint2(rv::Point<_Tp>& value) const;
        template<typename _Tp> bool tryGetAngle(_Tp& value) const;
        template<typename _Tp> bool tryGetWidth(_Tp& value) const;
        template<typename _Tp> bool tryGetHeight(_Tp& value) const;
        template<typename _Tp> bool tryGetSize(rv::Size<_Tp>& value) const;

        template<typename _Tp> bool tryGetLine(rv::Line<_Tp>& value) const;
        template<typename _Tp> bool tryGetPose(rv::Pose<_Tp>& value) const;
        template<typename _Tp> bool tryGetCircle(rv::Circle<_Tp>& value) const;
        template<typename _Tp> bool tryGetRect(rv::RotatedRect<_Tp>& value) const;

    public:
        double x;
        double y;
        double w;
        double h;
        double angle;
        double x2;
        double y2;

        rv::GeometryType type = rv::GeometryType::None;

    };


}

#include "variant_geometry.inl"