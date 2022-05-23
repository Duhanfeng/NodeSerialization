#pragma once

#include "point.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Circle
    {
    public:

        //构造
        constexpr Circle() noexcept;
        constexpr Circle(_Tp x, _Tp y, _Tp radius) noexcept;
        constexpr Circle(const Point<_Tp>& center, _Tp radius) noexcept;
        template<typename _Tp2> constexpr Circle(const Circle<_Tp2>& circle) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr _Tp area() const noexcept;
        inline constexpr _Tp perimeter() const noexcept;
        inline constexpr Circle move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Circle rotate(const Point<_Tp>& center, double radian) const noexcept;

        inline constexpr Point<_Tp> centerLeft() const noexcept;
        inline constexpr Point<_Tp> centerTop() const noexcept;
        inline constexpr Point<_Tp> centerRight() const noexcept;
        inline constexpr Point<_Tp> centerBottom() const noexcept;
        inline constexpr _Tp left() const noexcept;
        inline constexpr _Tp top() const noexcept;
        inline constexpr _Tp right() const noexcept;
        inline constexpr _Tp bottom() const noexcept;

        //符号重载
        inline constexpr Circle& operator*=(double c) noexcept;
        inline constexpr Circle& operator/=(double c);
        template<typename _Tp2> inline constexpr Circle& operator= (const Circle<_Tp2>&) noexcept;  //类型转换

        //核心数据
        Point<_Tp> center;  //圆心
        _Tp radius;         //半径

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Circle<_Tp>&, const Circle<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Circle<_Tp>&, const Circle<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Circle<_Tp> operator*(const Circle<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Circle<_Tp> operator*(double, const Circle<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Circle<_Tp> operator/(const Circle<_Tp>&, double);
}

#include "circle.inl"