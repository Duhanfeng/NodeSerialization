#pragma once

#include "point.hpp"
#include "size.hpp"
#include "rectangle.hpp"

namespace rv
{
    template<typename _Tp = double>
    class RotatedRect
    {
    public:

        //构造
        constexpr RotatedRect() noexcept;
        constexpr RotatedRect(_Tp x, _Tp y, _Tp w, _Tp h, double angle) noexcept;
        constexpr RotatedRect(const Point<_Tp>& center, const Size<_Tp>& size, double angle) noexcept;
        constexpr RotatedRect(const Rectangle<_Tp>& rect, double angle) noexcept;
        template<typename _Tp2> constexpr RotatedRect(const RotatedRect<_Tp2>& rect) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr _Tp area() const noexcept;
        inline constexpr RotatedRect move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr RotatedRect rotate(const Point<_Tp>& center, double radian) const noexcept;

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
        inline constexpr RotatedRect& operator*=(double c) noexcept;
        inline constexpr RotatedRect& operator/=(double c);
        template<typename _Tp2> inline constexpr RotatedRect& operator= (const RotatedRect<_Tp2>&) noexcept;  //类型转换

        //核心数据
        Point<_Tp> center;
        Size<_Tp> size;
        double angle;       //角度,弧度制
    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const RotatedRect<_Tp>&, const RotatedRect<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const RotatedRect<_Tp>&, const RotatedRect<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const RotatedRect<_Tp> operator*(const RotatedRect<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const RotatedRect<_Tp> operator*(double, const RotatedRect<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const RotatedRect<_Tp> operator/(const RotatedRect<_Tp>&, double);
}

#include "rotatedRect.inl"