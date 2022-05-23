#pragma once

namespace rv
{
    template<typename _Tp = double>
    class Point
    {
    public:

        //构造
        constexpr Point() noexcept;
        constexpr Point(_Tp x, _Tp y) noexcept;
        template<typename _Tp2> constexpr Point(const Point<_Tp2>& point) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr double distance(const Point& point) const noexcept;
        inline constexpr double angle(const Point& point) const noexcept;                           //目标点相对于当前点的角度
        inline constexpr Point move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Point rotate(const Point& center, double radian) const noexcept;

        //符号重载
        inline constexpr Point& operator+=(const Point&) noexcept;
        inline constexpr Point& operator-=(const Point&) noexcept;
        inline constexpr Point& operator*=(double c) noexcept;
        inline constexpr Point& operator/=(double c);
        template<typename _Tp2> inline constexpr Point& operator= (const Point<_Tp2>&) noexcept;    //类型转换

        //核心数据
        _Tp x;
        _Tp y;
    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Point<_Tp>&, const Point<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Point<_Tp>&, const Point<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Point<_Tp> operator+(const Point<_Tp>&, const Point<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Point<_Tp> operator-(const Point<_Tp>&, const Point<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Point<_Tp> operator*(const Point<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Point<_Tp> operator*(double, const Point<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Point<_Tp> operator/(const Point<_Tp>&, double);

    template<typename _Tp> inline constexpr const Point<_Tp> rotatePoint(const Point<_Tp>& center, const Point<_Tp>& p1, double radian) noexcept;

}

#include "point.inl"