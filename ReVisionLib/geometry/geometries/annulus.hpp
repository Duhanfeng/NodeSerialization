#pragma once

#include "point.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Annulus
    {
    public:

        //构造
        constexpr Annulus() noexcept;
        constexpr Annulus(_Tp x, _Tp y, _Tp radius1, _Tp radius2, double angleStart, double angleEnd) noexcept;
        constexpr Annulus(const Point<_Tp>& center, _Tp radius1, _Tp radius2, double angleStart, double angleEnd) noexcept;
        template<typename _Tp2> constexpr Annulus(const Annulus<_Tp2>& annulus) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr Annulus move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Annulus rotate(const Point<_Tp>& center, double radian) const noexcept;
        inline constexpr double angleSpan() const noexcept;             //获取角度跨度
        inline constexpr bool checkAngle(double angle) const noexcept;  //检查某个角度在圆环有效角度上

        //符号重载
        inline constexpr Annulus& operator*=(double c) noexcept;
        inline constexpr Annulus& operator/=(double c);
        template<typename _Tp2> inline constexpr Annulus& operator= (const Annulus<_Tp2>&) noexcept;  //类型转换

        //核心数据
        Point<_Tp> center;  //圆心
        _Tp radius1;        //内径
        _Tp radius2;        //外径
        double angleStart;  //起始角度
        double angleEnd;    //终止角度(定义:永远从起始角度顺时针旋转到终止角度)

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Annulus<_Tp>&, const Annulus<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Annulus<_Tp>&, const Annulus<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Annulus<_Tp> operator*(const Annulus<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Annulus<_Tp> operator*(double, const Annulus<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Annulus<_Tp> operator/(const Annulus<_Tp>&, double);
}

#include "annulus.inl"