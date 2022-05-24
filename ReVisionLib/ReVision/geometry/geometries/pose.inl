#include "pose.hpp"
#include "ReVision/rmath.h"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Pose<_Tp>::Pose() noexcept : center(), angle()
    {
    }

    template<typename _Tp>
    inline constexpr rv::Pose<_Tp>::Pose(_Tp x, _Tp y, double _angle) noexcept :
        center(x, y),
        angle(_angle)
    {
    }

    template<typename _Tp>
    inline constexpr rv::Pose<_Tp>::Pose(const Point<_Tp>& _center, double _angle) noexcept :
        center(_center), 
        angle(_angle)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Pose<_Tp>::Pose(const Pose<_Tp2>& pose) noexcept
    {
        center = Point<_Tp>(pose.center);
        angle = pose.angle;
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Pose<_Tp>& Pose<_Tp>::operator=(const Pose<_Tp2>& pose) noexcept
    {
        center = Point<_Tp>(pose.center);
        angle = pose.angle;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool Pose<_Tp>::isNull() const noexcept
    {
        return center.isNull();
    }

    template<typename _Tp>
    inline constexpr Pose<_Tp> Pose<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Pose<_Tp>(center.move(dx, dy), angle);
    }

    template<typename _Tp>
    inline constexpr Pose<_Tp> Pose<_Tp>::rotate(const Point<_Tp>& _center, double radian) const noexcept
    {
        return Pose<_Tp>(center.rotate(_center, radian), angle + radian);
    }

    template<typename _Tp>
    inline constexpr void Pose<_Tp>::createTransferMatrix(const Pose<_Tp>& dst) const noexcept
    {

    }

    template<typename _Tp>
    inline constexpr Pose<_Tp>& Pose<_Tp>::operator*=(double c) noexcept
    {
        center *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Pose<_Tp>& Pose<_Tp>::operator/=(double c)
    {
        center /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Pose<_Tp>& pose1, const Pose<_Tp>& pose2) noexcept
    {
        return (pose1.center == pose2.center) && fuzzyCompare(pose1.angle, pose2.angle);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Pose<_Tp>& pose1, const Pose<_Tp>& pose2) noexcept
    {
        return (pose1.center != pose2.center) || !fuzzyCompare(pose1.angle, pose2.angle);
    }

    template<typename _Tp>
    inline constexpr const Pose<_Tp> operator*(const Pose<_Tp>& pose, double c) noexcept
    {
        return Pose<_Tp>(pose.center * c, pose.angle);
    }

    template<typename _Tp>
    inline constexpr const Pose<_Tp> operator*(double c, const Pose<_Tp>& pose) noexcept
    {
        return Pose<_Tp>(pose.center * c, pose.angle);
    }

    template<typename _Tp>
    inline constexpr const Pose<_Tp> operator/(const Pose<_Tp>& pose, double c)
    {
        return Pose<_Tp>(pose.center / c, pose.angle);
    }

}