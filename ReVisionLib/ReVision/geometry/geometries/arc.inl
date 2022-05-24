#include "arc.hpp"
#include "ReVision/rmath.h"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Arc<_Tp>::Arc() noexcept :
        center(0, 0),
        radius(0),
        angleStart(_Tp(0)), 
        angleEnd(_Tp(0))
    {
    }

    template<typename _Tp>
    inline constexpr rv::Arc<_Tp>::Arc(_Tp x, _Tp y, _Tp _radius, double _angleStart, double _angleEnd) noexcept :
        center(x, y),
        radius(_radius),
        angleStart(_angleStart),
        angleEnd(_angleEnd)
    {
    }

    template<typename _Tp>
    inline constexpr rv::Arc<_Tp>::Arc(const Point<_Tp>& _center, _Tp _radius, double _angleStart, double _angleEnd) noexcept :
        center(_center),
        radius(_radius),
        angleStart(_angleStart),
        angleEnd(_angleEnd)
    {
    }

    template<typename _Tp>
    inline constexpr rv::Arc<_Tp>::Arc(const Circle<_Tp>& _circle, double _startAngle, double _endAngle) noexcept :
        center(_circle.center),
        radius(_circle.radius),
        angleStart(_startAngle),
        angleEnd(_endAngle)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Arc<_Tp>::Arc(const Arc<_Tp2>& arc) noexcept
    {
        center = Point<_Tp>(arc.center);
        radius = _Tp(arc.radius);
        angleStart = arc.angleStart;
        angleEnd = arc.angleEnd;
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Arc<_Tp>& Arc<_Tp>::operator=(const Arc<_Tp2>& arc) noexcept
    {
        center = Point<_Tp>(arc.center);
        radius = _Tp(arc.radius);
        angleStart = arc.angleStart;
        angleEnd = arc.angleEnd;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool Arc<_Tp>::isNull() const noexcept
    {
        return isNull(radius);
    }

    template<typename _Tp>
    inline constexpr Arc<_Tp> Arc<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Arc<_Tp>(center.move(dx, dy), radius, angleStart, angleEnd);
    }

    template<typename _Tp>
    inline constexpr Arc<_Tp> Arc<_Tp>::rotate(const Point<_Tp>& _center, double _radian) const noexcept
    {
        return Arc<_Tp>(center.rotate(_center, _radian), radius, angleStart + _radian, angleEnd + _radian);
    }
    
    template<typename _Tp>
    inline constexpr double Arc<_Tp>::angleSpan() const noexcept
    {
        double span = angleEnd - angleStart;

        //将角度跨度描述限制在[0,360]
        while (span < 0)
        {
            span += 2 * RV_PI;
        }
        if (span > 2 * RV_PI)
        {
            span = 2 * RV_PI;
        }

        return span;
    }

    template<typename _Tp>
    inline constexpr bool Arc<_Tp>::checkAngle(double angle) const noexcept
    {
        //将angle限制在[start,start+2pi]之中
        while (angle < angleStart)
        {
            angle += 2 * RV_PI;
        }
        while (angle > (angleStart + 2 * RV_PI))
        {
            angle -= 2 * RV_PI;
        }

        return ((angle >= angleStart) && (angle <= (angleStart + angleSpan())));
    }

    template<typename _Tp>
    inline constexpr Arc<_Tp>& Arc<_Tp>::operator*=(double c) noexcept
    {
        center *= c;
        radius *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Arc<_Tp>& Arc<_Tp>::operator/=(double c)
    {
        center /= c;
        radius /= c;
        return *this;
    }

    template<typename _Tp>
    constexpr bool operator==(const Arc<_Tp>& arc1, const Arc<_Tp>& arc2) noexcept
    {
        return (arc1.center == arc2.center) &&
            fuzzyCompare(arc1.radius, arc2.radius)&&
            fuzzyCompare(arc1.angleStart, arc2.angleStart)&&
            fuzzyCompare(arc1.angleSpan(), arc2.angleSpan());
    }

    template<typename _Tp>
    constexpr bool operator!=(const Arc<_Tp>& arc1, const Arc<_Tp>& arc2) noexcept
    {
        return (arc1.center != arc2.center) ||
            !fuzzyCompare(arc1.radius, arc2.radius) ||
            !fuzzyCompare(arc1.angleStart, arc2.angleStart) ||
            !fuzzyCompare(arc1.angleSpan(), arc2.angleSpan());
    }
    template<typename _Tp>
    constexpr const Arc<_Tp> operator*(const Arc<_Tp>& arc, double c) noexcept
    {
        return Arc<_Tp>(arc.center * c, arc.radius * c, arc.angleStart, arc.angleEnd);
    }

    template<typename _Tp>
    constexpr const Arc<_Tp> operator*(double c, const Arc<_Tp>& arc) noexcept
    {
        return Arc<_Tp>(arc.center * c, arc.radius * c, arc.angleStart, arc.angleEnd);;
    }

    template<typename _Tp>
    constexpr const Arc<_Tp> operator/(const Arc<_Tp>& arc, double c)
    {
        return Arc<_Tp>(arc.center / c, arc.radius / c, arc.angleStart, arc.angleEnd);
    }
}