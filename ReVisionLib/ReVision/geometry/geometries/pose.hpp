#pragma once

#include "point.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Pose
    {
    public:

        //构造
        constexpr Pose() noexcept;
        constexpr Pose(_Tp x, _Tp y, double angle) noexcept;
        constexpr Pose(const Point<_Tp>& center, double angle) noexcept;
        template<typename _Tp2> constexpr Pose(const Pose<_Tp2>& ray) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr Pose move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Pose rotate(const Point<_Tp>& center, double radian) const noexcept;
        inline constexpr void createTransferMatrix(const Pose<_Tp>& dst) const noexcept;    //创建从当前点到目标点的转换矩阵(需要opencv库,预留)

        //符号重载
        inline constexpr Pose& operator*=(double c) noexcept;
        inline constexpr Pose& operator/=(double c);
        template<typename _Tp2> inline constexpr Pose& operator= (const Pose<_Tp2>&) noexcept;  //类型转换

        //核心数据
        Point<_Tp> center;  //中心(锚点)
        double angle;       //角度

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Pose<_Tp>&, const Pose<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Pose<_Tp>&, const Pose<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Pose<_Tp> operator*(const Pose<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Pose<_Tp> operator*(double, const Pose<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Pose<_Tp> operator/(const Pose<_Tp>&, double);

}

#include "pose.inl"