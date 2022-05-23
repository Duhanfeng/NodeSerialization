#include "rotatedRect.hpp"
#include "rmath.h"
#include "point.hpp"
#include "size.hpp"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::RotatedRect<_Tp>::RotatedRect() noexcept : center(), size()
    {
    }

    template<typename _Tp>
    inline constexpr rv::RotatedRect<_Tp>::RotatedRect(_Tp x, _Tp y, _Tp w, _Tp h, double _angle) noexcept : 
        center(x, y), 
        size(w, h),
        angle(_angle)
    {
    }

    template<typename _Tp>
    inline constexpr rv::RotatedRect<_Tp>::RotatedRect(const Point<_Tp>& _center, const Size<_Tp>& _size, double _angle) noexcept :
        center(_center), 
        size(_size),
        angle(_angle)
    {
    }

    template<typename _Tp>
    inline constexpr rv::RotatedRect<_Tp>::RotatedRect(const Rectangle<_Tp>& rect, double _angle) noexcept :
        center(rect.center),
        size(rect.size),
        angle(_angle)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr RotatedRect<_Tp>::RotatedRect(const RotatedRect<_Tp2>& rect) noexcept
    {
        center = Point<_Tp>(rect.center);
        size = Size<_Tp>(rect.size);
        angle = rect.angle;
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr RotatedRect<_Tp>& RotatedRect<_Tp>::operator=(const RotatedRect<_Tp2>& rect) noexcept
    {
        center = Point<_Tp>(rect.center);
        size = Size<_Tp>(rect.size);
        angle = rect.angle;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool RotatedRect<_Tp>::isNull() const noexcept
    {
        return size.isNull();
    }

    template<typename _Tp>
    inline constexpr _Tp RotatedRect<_Tp>::area() const noexcept
    {
        return size.area();
    }

    template<typename _Tp>
    inline constexpr RotatedRect<_Tp> RotatedRect<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return RotatedRect<_Tp>(center.move(dx, dy), size, angle);
    }

    template<typename _Tp>
    inline constexpr RotatedRect<_Tp> RotatedRect<_Tp>::rotate(const Point<_Tp>& _center, double radian) const noexcept
    {
        return RotatedRect<_Tp>(center.rotate(_center, radian), size, angle + radian);
    }

    template<typename _Tp>
    inline constexpr RotatedRect<_Tp>& RotatedRect<_Tp>::operator*=(double c) noexcept
    {
        center *= c;
        size *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr RotatedRect<_Tp>& RotatedRect<_Tp>::operator/=(double c)
    {
        center /= c;
        size /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const RotatedRect<_Tp>& rect1, const RotatedRect<_Tp>& rect2) noexcept
    {
        return (rect1.center == rect2.center) && (rect1.size == rect2.size) && fuzzyCompare(rect1.angle, rect2.angle);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const RotatedRect<_Tp>& rect1, const RotatedRect<_Tp>& rect2) noexcept
    {
        return (rect1.center != rect2.center) || (rect1.size != rect2.size) || !fuzzyCompare(rect1.angle, rect2.angle);
    }

    template<typename _Tp>
    inline constexpr const RotatedRect<_Tp> operator*(const RotatedRect<_Tp>& rect, double c) noexcept
    {
        return RotatedRect<_Tp>(rect.center * c, rect.size * c, rect.angle);
    }

    template<typename _Tp>
    inline constexpr const RotatedRect<_Tp> operator*(double c, const RotatedRect<_Tp>& rect) noexcept
    {
        return RotatedRect<_Tp>(rect.center * c, rect.size * c, rect.angle);
    }

    template<typename _Tp>
    inline constexpr const RotatedRect<_Tp> operator/(const RotatedRect<_Tp>& rect, double c)
    {
        return RotatedRect<_Tp>(rect.center / c, rect.size / c, rect.angle);
    }

    template<typename _Tp>
    inline constexpr std::vector<Point<_Tp>> RotatedRect<_Tp>::getPoints() const noexcept
    {
        std::vector<Point<_Tp>> points(4);
        _Tp length1 = _Tp(size.width / 2.0);
        _Tp length2 = _Tp(size.height / 2.0);
        points[0] = Point<_Tp>(center.x - length1, center.y - length2);
        points[1] = Point<_Tp>(center.x + length1, center.y - length2);
        points[2] = Point<_Tp>(center.x + length1, center.y + length2);
        points[3] = Point<_Tp>(center.x - length1, center.y + length2);

        std::vector<Point<_Tp>> points2(4);
        points2[0] = points[0].rotate(center, angle);
        points2[1] = points[1].rotate(center, angle);
        points2[2] = points[2].rotate(center, angle);
        points2[3] = points[3].rotate(center, angle);

        return points2;
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::topLeft() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x - length1, center.y - length2).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::topRight() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x + length1, center.y - length2).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::bottomRight() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x + length1, center.y + length2).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::bottomLeft() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x - length1, center.y + length2).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::centerLeft() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        return Point<_Tp>(center.x - length1, center.y).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::centerTop() const noexcept
    {
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x, center.y - length2).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::centerRight() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        return Point<_Tp>(center.x + length1, center.y).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> RotatedRect<_Tp>::centerBottom() const noexcept
    {
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x, center.y + length2).rotate(center, angle);
    }

    template<typename _Tp>
    inline constexpr _Tp RotatedRect<_Tp>::left() const noexcept
    {
        return centerLeft().x;
    }

    template<typename _Tp>
    inline constexpr _Tp RotatedRect<_Tp>::top() const noexcept
    {
        return centerTop().y;
    }

    template<typename _Tp>
    inline constexpr _Tp RotatedRect<_Tp>::right() const noexcept
    {
        return centerRight().x;
    }

    template<typename _Tp>
    inline constexpr _Tp RotatedRect<_Tp>::bottom() const noexcept
    {
        return centerBottom().y;
    }
}