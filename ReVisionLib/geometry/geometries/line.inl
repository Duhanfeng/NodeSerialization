#include "line.hpp"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Line<_Tp>::Line() noexcept : p1(), p2()
    {
    }

    template<typename _Tp>
    inline constexpr rv::Line<_Tp>::Line(_Tp x1, _Tp y1, _Tp x2, _Tp y2) noexcept : p1(x1, y1), p2(x2, y2)
    {
    }

    template<typename _Tp>
    inline constexpr rv::Line<_Tp>::Line(const Point<_Tp>& _p1, const Point<_Tp>& _p2) noexcept : p1(_p1), p2(_p2)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Line<_Tp>::Line(const Line<_Tp2>& line) noexcept
    {
        p1 = Point<_Tp>(line.p1);
        p2 = Point<_Tp>(line.p2);
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Line<_Tp>& Line<_Tp>::operator=(const Line<_Tp2>& line) noexcept
    {
        p1 = Point<_Tp>(line.p1);
        p2 = Point<_Tp>(line.p2);
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool Line<_Tp>::isNull() const noexcept
    {
        return p1.isNull() && p2.isNull();
    }

    template<typename _Tp>
    inline constexpr _Tp Line<_Tp>::length() const noexcept
    {
        return p1.distance(p2);
    }

    template<typename _Tp>
    inline constexpr double Line<_Tp>::angle() const noexcept
    {
        return p1.angle(p2);
    }

    template<typename _Tp>
    inline constexpr Line<_Tp> Line<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Line<_Tp>(p1.move(dx, dy), p2.move(dx, dy));
    }

    template<typename _Tp>
    inline constexpr Line<_Tp> Line<_Tp>::rotate(const Point<_Tp>& center, double radian) const noexcept
    {
        return Line<_Tp>(p1.rotate(center, radian), p2.rotate(center, radian));
    }

    template<typename _Tp>
    inline constexpr Line<_Tp>& Line<_Tp>::operator*=(double c) noexcept
    {
        p1 *= c;
        p2 *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Line<_Tp>& Line<_Tp>::operator/=(double c)
    {
        p1 /= c;
        p2 /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Line<_Tp>& line1, const Line<_Tp>& line2) noexcept
    {
        return (line1.p1 == line2.p1) && (line1.p2 == line2.p2);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Line<_Tp>& line1, const Line<_Tp>& line2) noexcept
    {
        return (line1.p1 != line2.p1) || (line1.p2 != line2.p2);
    }

    template<typename _Tp>
    inline constexpr const Line<_Tp> operator*(const Line<_Tp>& line, double c) noexcept
    {
        return Line<_Tp>(line.p1 * c, line.p2 * c);
    }

    template<typename _Tp>
    inline constexpr const Line<_Tp> operator*(double c, const Line<_Tp>& line) noexcept
    {
        return Line<_Tp>(line.p1 * c, line.p2 * c);
    }

    template<typename _Tp>
    inline constexpr const Line<_Tp> operator/(const Line<_Tp>& line, double c)
    {
        return Line<_Tp>(line.p1 / c, line.p2 / c);
    }

}