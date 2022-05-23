#pragma once

#include "point.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Ray
    {
    public:

        //构造
        constexpr Ray() noexcept;
        constexpr Ray(_Tp x, _Tp y, double angle) noexcept;
        constexpr Ray(const Point<_Tp>& center, double angle) noexcept;
        template<typename _Tp2> constexpr Ray(const Ray<_Tp2>& ray) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr Ray move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Ray rotate(const Point<_Tp>& center, double radian) const noexcept;
        inline constexpr Point<_Tp> getRayDstPoint(double length) const noexcept;    //获取当前射线方向指定长度的目标点

        //符号重载
        inline constexpr Ray& operator*=(double c) noexcept;
        inline constexpr Ray& operator/=(double c);
        template<typename _Tp2> inline constexpr Ray& operator= (const Ray<_Tp2>&) noexcept;  //类型转换

        //核心数据
        Point<_Tp> center;  //中心(锚点)
        double angle;       //角度

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Ray<_Tp>&, const Ray<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Ray<_Tp>&, const Ray<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Ray<_Tp> operator*(const Ray<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Ray<_Tp> operator*(double, const Ray<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Ray<_Tp> operator/(const Ray<_Tp>&, double);
}

#include "ray.inl"