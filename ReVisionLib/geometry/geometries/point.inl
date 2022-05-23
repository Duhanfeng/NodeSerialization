#include "point.hpp"
#include "rmath.h"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Point<_Tp>::Point() noexcept : x(_Tp(0)), y(_Tp(0))
    {
    }

    template<typename _Tp>
    inline constexpr rv::Point<_Tp>::Point(_Tp _x, _Tp _y) noexcept : x(_x), y(_y)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Point<_Tp>::Point(const Point<_Tp2>& point) noexcept
    {
        x = _Tp(point.x);
        y = _Tp(point.y);
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Point<_Tp>& Point<_Tp>::operator=(const Point<_Tp2>& point) noexcept
    {
        x = _Tp(point.x);
        y = _Tp(point.y);
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool rv::Point<_Tp>::isNull() const noexcept
    {
        return isNull(x) && isNull(y);
    }

    template<typename _Tp>
    inline constexpr double Point<_Tp>::distance(const Point& point) const noexcept
    {
        return std::sqrt((double)((point.x - x) * (point.x - x) + (point.y - y) * (point.y - y)));
    }

    template<typename _Tp>
    inline constexpr double Point<_Tp>::angle(const Point& point) const noexcept
    {
        return std::atan2(point.y - y, point.x - x);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Point<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Point(x + dx, y + dy);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Point<_Tp>::rotate(const Point& center, double radian) const noexcept
    {
        _Tp _x = _Tp((x - center.x) * std::cos(radian) - (y - center.y) * std::sin(radian) + center.x);
        _Tp _y = _Tp((x - center.x) * std::sin(radian) + (y - center.y) * std::cos(radian) + center.y);
        return Point(_x, _y);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp>& Point<_Tp>::operator+=(const Point& point) noexcept
    {
        x += point.x;
        y += point.y;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Point<_Tp>& Point<_Tp>::operator-=(const Point& point) noexcept
    {
        x -= point.x;
        y -= point.y;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Point<_Tp>& Point<_Tp>::operator*=(double c) noexcept
    {
        x *= c;
        y *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Point<_Tp>& Point<_Tp>::operator/=(double c)
    {
        x /= c;
        y /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Point<_Tp>& point1, const Point<_Tp>& point2) noexcept
    {
        return fuzzyCompare(point1.x, point2.x) && fuzzyCompare(point1.y, point2.y);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Point<_Tp>& point1, const Point<_Tp>& point2) noexcept
    {
        return !fuzzyCompare(point1.x, point2.x) || !fuzzyCompare(point1.y, point2.y);
    }

    template<typename _Tp>
    inline constexpr const Point<_Tp> operator+(const Point<_Tp>& point1, const Point<_Tp>& point2) noexcept
    {
        return Point<_Tp>(point1.x + point2.x, point1.y + point2.y);
    }

    template<typename _Tp>
    inline constexpr const Point<_Tp> operator-(const Point<_Tp>& point1, const Point<_Tp>& point2) noexcept
    {
        return Point<_Tp>(point1.x - point2.x, point1.y - point2.y);
    }

    template<typename _Tp>
    inline constexpr const Point<_Tp> operator*(const Point<_Tp>& point, double c) noexcept
    {
        return Point<_Tp>(point.x * c, point.y * c);
    }

    template<typename _Tp>
    inline constexpr const Point<_Tp> operator*(double c, const Point<_Tp>& point) noexcept
    {
        return Point<_Tp>(point.x * c, point.y * c);
    }

    template<typename _Tp>
    inline constexpr const Point<_Tp> operator/(const Point<_Tp>& point, double c)
    {
        return Point<_Tp>(point.x / c, point.y / c);
    }

    template<typename _Tp>
    inline constexpr const Point<_Tp> rotatePoint(const Point<_Tp>& center, const Point<_Tp>& p1, double radian) noexcept
    {
        _Tp p2x, p2y;
        rotatePoint(center.x, center.y, p1.x, p1.y, radian, p2x, p2y);
        return Point<_Tp>(p2x, p2y);
    }

}