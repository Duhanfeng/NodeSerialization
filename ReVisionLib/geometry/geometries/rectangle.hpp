#pragma once

#include <vector>
#include "point.hpp"
#include "size.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Rectangle
    {
    public:

        //构造
        constexpr Rectangle() noexcept;
        constexpr Rectangle(_Tp x, _Tp y, _Tp w, _Tp h) noexcept;
        constexpr Rectangle(const Point<_Tp>& center, const Size<_Tp>& size) noexcept;
        template<typename _Tp2> constexpr Rectangle(const Rectangle<_Tp2>& rect) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr _Tp area() const noexcept;
        inline constexpr Rectangle move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Rectangle rotate(const Point<_Tp>& center, double radian) const noexcept;

        inline constexpr std::vector<Point<_Tp>> getPoints() const noexcept;    //顺序为:左上,右上,右下,左下
        inline constexpr Point<_Tp> topLeft() const noexcept;
        inline constexpr Point<_Tp> topRight() const noexcept;
        inline constexpr Point<_Tp> bottomRight() const noexcept;
        inline constexpr Point<_Tp> bottomLeft() const noexcept;
        inline constexpr Point<_Tp> centerLeft() const noexcept;
        inline constexpr Point<_Tp> centerTop() const noexcept;
        inline constexpr Point<_Tp> centerRight() const noexcept;
        inline constexpr Point<_Tp> centerBottom() const noexcept;
        inline constexpr _Tp left() const noexcept;
        inline constexpr _Tp top() const noexcept;
        inline constexpr _Tp right() const noexcept;
        inline constexpr _Tp bottom() const noexcept;

        //符号重载
        inline constexpr Rectangle& operator*=(double c) noexcept;
        inline constexpr Rectangle& operator/=(double c);
        template<typename _Tp2> inline constexpr Rectangle& operator= (const Rectangle<_Tp2>&) noexcept;  //类型转换

        //核心数据
        Point<_Tp> center;
        Size<_Tp> size;
    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Rectangle<_Tp>&, const Rectangle<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Rectangle<_Tp>&, const Rectangle<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Rectangle<_Tp> operator*(const Rectangle<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Rectangle<_Tp> operator*(double, const Rectangle<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Rectangle<_Tp> operator/(const Rectangle<_Tp>&, double);
}

#include "rectangle.inl"