#pragma once

#include "point.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Line
    {
    public:

        //构造
        constexpr Line() noexcept;
        constexpr Line(_Tp x1, _Tp y1, _Tp x2, _Tp y2) noexcept;
        constexpr Line(const Point<_Tp>& p1, const Point<_Tp>& p2) noexcept;
        template<typename _Tp2> constexpr Line(const Line<_Tp2>& line) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr _Tp length() const noexcept;
        inline constexpr double angle() const noexcept;
        inline constexpr Line move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Line rotate(const Point<_Tp>& center, double radian) const noexcept;

        //符号重载
        inline constexpr Line& operator*=(double c) noexcept;
        inline constexpr Line& operator/=(double c);
        template<typename _Tp2> inline constexpr Line& operator= (const Line<_Tp2>&) noexcept;  //类型转换

        //核心数据
        Point<_Tp> p1;
        Point<_Tp> p2;
    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Line<_Tp>&, const Line<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Line<_Tp>&, const Line<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Line<_Tp> operator*(const Line<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Line<_Tp> operator*(double, const Line<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Line<_Tp> operator/(const Line<_Tp>&, double);
}

#include "line.inl"