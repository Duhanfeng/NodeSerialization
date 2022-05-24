#include "annulus.hpp"
#include "ReVision/rmath.h"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Annulus<_Tp>::Annulus() noexcept : 
        center(), 
        radius1(_Tp(0)),
        radius2(_Tp(0)),
        angleStart(_Tp(0)),
        angleEnd(_Tp(0))
    {
    }

    template<typename _Tp>
    inline constexpr rv::Annulus<_Tp>::Annulus(_Tp x, _Tp y, _Tp _radius1, _Tp _radius2, double _angleStart, double _angleEnd) noexcept :
        center(x, y),
        radius1(_radius1),
        radius2(_radius2),
        angleStart(_angleStart),
        angleEnd(_angleEnd)
    {
    }

    template<typename _Tp>
    inline constexpr rv::Annulus<_Tp>::Annulus(const Point<_Tp>& _center, _Tp _radius1, _Tp _radius2, double _angleStart, double _angleEnd) noexcept :
        center(_center),
        radius1(_radius1),
        radius2(_radius2),
        angleStart(_angleStart),
        angleEnd(_angleEnd)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Annulus<_Tp>::Annulus(const Annulus<_Tp2>& annulus) noexcept
    {
        center = Point<_Tp>(annulus.center);
        radius1 = _Tp(annulus.radius1);
        radius2 = _Tp(annulus.radius2);
        angleStart = annulus.angleStart;
        angleEnd = annulus.angleEnd;
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Annulus<_Tp>& Annulus<_Tp>::operator=(const Annulus<_Tp2>& annulus) noexcept
    {
        center = Point<_Tp>(annulus.center);
        radius1 = _Tp(annulus.radius1);
        radius2 = _Tp(annulus.radius2);
        angleStart = annulus.angleStart;
        angleEnd = annulus.angleEnd;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool Annulus<_Tp>::isNull() const noexcept
    {
        return isNull(radius1) && isNull(radius2);
    }

    template<typename _Tp>
    inline constexpr Annulus<_Tp> Annulus<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Annulus<_Tp>(center.move(dx, dy), radius1, radius2, angleStart, angleEnd);
    }

    template<typename _Tp>
    inline constexpr Annulus<_Tp> Annulus<_Tp>::rotate(const Point<_Tp>& _center, double radian) const noexcept
    {
        return Annulus<_Tp>(center.rotate(_center, radian), radius1, radius2, angleStart, angleEnd);
    }

    template<typename _Tp>
    inline constexpr double Annulus<_Tp>::angleSpan() const noexcept
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
    inline constexpr bool Annulus<_Tp>::checkAngle(double angle) const noexcept
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
    inline constexpr Annulus<_Tp>& Annulus<_Tp>::operator*=(double c) noexcept
    {
        center *= c;
        radius1 *= c;
        radius2 *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Annulus<_Tp>& Annulus<_Tp>::operator/=(double c)
    {
        center /= c;
        radius1 /= c;
        radius2 /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Annulus<_Tp>& annulus1, const Annulus<_Tp>& annulus2) noexcept
    {
        return (annulus1.center == annulus2.center) &&
            fuzzyCompare(annulus1.radius1, annulus2.radius1) &&
            fuzzyCompare(annulus1.radius2, annulus2.radius2) &&
            fuzzyCompare(annulus1.angleStart, annulus2.angleStart) &&
            fuzzyCompare(annulus1.angleSpan(), annulus2.angleSpan());
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Annulus<_Tp>& annulus1, const Annulus<_Tp>& annulus2) noexcept
    {
        return (annulus1.center != annulus2.center) ||
            !fuzzyCompare(annulus1.radius1, annulus2.radius1) ||
            !fuzzyCompare(annulus1.radius2, annulus2.radius2) ||
            !fuzzyCompare(annulus1.angleStart, annulus2.angleStart) ||
            !fuzzyCompare(annulus1.angleSpan(), annulus2.angleSpan());
    }

    template<typename _Tp>
    inline constexpr const Annulus<_Tp> operator*(const Annulus<_Tp>& annulus, double c) noexcept
    {
        return Annulus<_Tp>(annulus.center * c, annulus.radius1 * c, annulus.radius2 * c, annulus.angleStart, annulus.angleEnd);
    }

    template<typename _Tp>
    inline constexpr const Annulus<_Tp> operator*(double c, const Annulus<_Tp>& annulus) noexcept
    {
        return Annulus<_Tp>(annulus.center * c, annulus.radius1 * c, annulus.radius2 * c, annulus.angleStart, annulus.angleEnd);
    }

    template<typename _Tp>
    inline constexpr const Annulus<_Tp> operator/(const Annulus<_Tp>& annulus, double c)
    {
        return Annulus<_Tp>(annulus.center / c, annulus.radius1 / c, annulus.radius2 / c, annulus.angleStart, annulus.angleEnd);
    }

}