#include "rectangle.hpp"
#include <vector>

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Rectangle<_Tp>::Rectangle() noexcept : center(), size()
    {
    }

    template<typename _Tp>
    inline constexpr rv::Rectangle<_Tp>::Rectangle(_Tp x, _Tp y, _Tp w, _Tp h) noexcept : center(x, y), size(w, h)
    {
    }

    template<typename _Tp>
    inline constexpr rv::Rectangle<_Tp>::Rectangle(const Point<_Tp>& _center, const Size<_Tp>& _size) noexcept : center(_center), size(_size)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Rectangle<_Tp>::Rectangle(const Rectangle<_Tp2>& rect) noexcept
    {
        center = Point<_Tp>(rect.center);
        size = Size<_Tp>(rect.size);
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Rectangle<_Tp>& Rectangle<_Tp>::operator=(const Rectangle<_Tp2>& rect) noexcept
    {
        center = Point<_Tp>(rect.center);
        size = Size<_Tp>(rect.size);
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool Rectangle<_Tp>::isNull() const noexcept
    {
        return size.isNull();
    }

    template<typename _Tp>
    inline constexpr _Tp Rectangle<_Tp>::area() const noexcept
    {
        return size.area();
    }

    template<typename _Tp>
    inline constexpr Rectangle<_Tp> Rectangle<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Rectangle<_Tp>(center.move(dx, dy), size);
    }

    template<typename _Tp>
    inline constexpr Rectangle<_Tp> Rectangle<_Tp>::rotate(const Point<_Tp>& _center, double radian) const noexcept
    {
        return Rectangle<_Tp>(center.rotate(_center, radian), size);
    }

    template<typename _Tp>
    inline constexpr Rectangle<_Tp>& Rectangle<_Tp>::operator*=(double c) noexcept
    {
        center *= c;
        size *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Rectangle<_Tp>& Rectangle<_Tp>::operator/=(double c)
    {
        center /= c;
        size /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Rectangle<_Tp>& rect1, const Rectangle<_Tp>& rect2) noexcept
    {
        return (rect1.center == rect2.center) && (rect1.size == rect2.size);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Rectangle<_Tp>& rect1, const Rectangle<_Tp>& rect2) noexcept
    {
        return (rect1.center != rect2.center) || (rect1.size != rect2.size);
    }

    template<typename _Tp>
    inline constexpr const Rectangle<_Tp> operator*(const Rectangle<_Tp>& rect, double c) noexcept
    {
        return Rectangle<_Tp>(rect.center * c, rect.size * c);
    }

    template<typename _Tp>
    inline constexpr const Rectangle<_Tp> operator*(double c, const Rectangle<_Tp>& rect) noexcept
    {
        return Rectangle<_Tp>(rect.center * c, rect.size * c);
    }

    template<typename _Tp>
    inline constexpr const Rectangle<_Tp> operator/(const Rectangle<_Tp>& rect, double c)
    {
        return Rectangle<_Tp>(rect.center / c, rect.size / c);
    }

    template<typename _Tp>
    inline constexpr std::vector<Point<_Tp>> Rectangle<_Tp>::getPoints() const noexcept
    {
        std::vector<Point<_Tp>> points(4);
        _Tp length1 = _Tp(size.width / 2.0);
        _Tp length2 = _Tp(size.height / 2.0);

        points[0] = Point<_Tp>(center.x - length1, center.y - length2);
        points[1] = Point<_Tp>(center.x + length1, center.y - length2);
        points[2] = Point<_Tp>(center.x + length1, center.y + length2);
        points[3] = Point<_Tp>(center.x - length1, center.y + length2);
        return points;
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::topLeft() const noexcept
    {
        return Point<_Tp>(center.x - _Tp(size.width / 2.0), center.y - _Tp(size.height / 2.0));
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::topRight() const noexcept
    {
        return Point<_Tp>(center.x + _Tp(size.width / 2.0), center.y - _Tp(size.height / 2.0));
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::bottomRight() const noexcept
    {
        return Point<_Tp>(center.x + _Tp(size.width / 2.0), center.y + _Tp(size.height / 2.0));
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::bottomLeft() const noexcept
    {
        return Point<_Tp>(center.x - _Tp(size.width / 2.0), center.y + _Tp(size.height / 2.0));
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::centerLeft() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        return Point<_Tp>(center.x - length1, center.y);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::centerTop() const noexcept
    {
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x, center.y - length2);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::centerRight() const noexcept
    {
        _Tp length1 = _Tp(size.width / 2.0);
        return Point<_Tp>(center.x + length1, center.y);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Rectangle<_Tp>::centerBottom() const noexcept
    {
        _Tp length2 = _Tp(size.height / 2.0);
        return Point<_Tp>(center.x, center.y + length2);
    }

    template<typename _Tp>
    inline constexpr _Tp Rectangle<_Tp>::left() const noexcept
    {
        return center.x - _Tp(size.width / 2.0);
    }

    template<typename _Tp>
    inline constexpr _Tp Rectangle<_Tp>::top() const noexcept
    {
        return center.y - _Tp(size.height / 2.0);
    }

    template<typename _Tp>
    inline constexpr _Tp Rectangle<_Tp>::right() const noexcept
    {
        return center.x + _Tp(size.width / 2.0);
    }

    template<typename _Tp>
    inline constexpr _Tp Rectangle<_Tp>::bottom() const noexcept
    {
        return center.y + _Tp(size.height / 2.0);
    }
}