#include "ray.hpp"
#include "ReVision/rmath.h"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Ray<_Tp>::Ray() noexcept : center(), angle()
    {
    }

    template<typename _Tp>
    inline constexpr rv::Ray<_Tp>::Ray(_Tp x, _Tp y, double _angle) noexcept :
        center(x, y),
        angle(_angle)
    {
    }

    template<typename _Tp>
    inline constexpr rv::Ray<_Tp>::Ray(const Point<_Tp>& _center, double _angle) noexcept :
        center(_center), 
        angle(_angle)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Ray<_Tp>::Ray(const Ray<_Tp2>& ray) noexcept
    {
        center = Point<_Tp>(ray.center);
        angle = ray.angle;
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Ray<_Tp>& Ray<_Tp>::operator=(const Ray<_Tp2>& ray) noexcept
    {
        center = Point<_Tp>(ray.center);
        angle = ray.angle;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool Ray<_Tp>::isNull() const noexcept
    {
        return center.isNull();
    }

    template<typename _Tp>
    inline constexpr Ray<_Tp> Ray<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Ray<_Tp>(center.move(dx, dy), angle);
    }

    template<typename _Tp>
    inline constexpr Ray<_Tp> Ray<_Tp>::rotate(const Point<_Tp>& _center, double radian) const noexcept
    {
        return Ray<_Tp>(center.rotate(_center, radian), angle + radian);
    }

    template<typename _Tp>
    inline constexpr Point<_Tp> Ray<_Tp>::getRayDstPoint(double length) const noexcept
    {
        double dx = length * std::cos(angle);
        double dy = length * std::sin(angle);
        return Point<_Tp>(_Tp(center.x + dx), _Tp(center.y + dy));
    }

    template<typename _Tp>
    inline constexpr Ray<_Tp>& Ray<_Tp>::operator*=(double c) noexcept
    {
        center *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Ray<_Tp>& Ray<_Tp>::operator/=(double c)
    {
        center /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Ray<_Tp>& ray1, const Ray<_Tp>& ray2) noexcept
    {
        return (ray1.center == ray2.center) && fuzzyCompare(ray1.angle, ray2.angle);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Ray<_Tp>& ray1, const Ray<_Tp>& ray2) noexcept
    {
        return (ray1.center != ray2.center) || !fuzzyCompare(ray1.angle, ray2.angle);
    }

    template<typename _Tp>
    inline constexpr const Ray<_Tp> operator*(const Ray<_Tp>& ray, double c) noexcept
    {
        return Ray<_Tp>(ray.center * c, ray.angle);
    }

    template<typename _Tp>
    inline constexpr const Ray<_Tp> operator*(double c, const Ray<_Tp>& ray) noexcept
    {
        return Ray<_Tp>(ray.center * c, ray.angle);
    }

    template<typename _Tp>
    inline constexpr const Ray<_Tp> operator/(const Ray<_Tp>& ray, double c)
    {
        return Ray<_Tp>(ray.center / c, ray.angle);
    }

}