#pragma once

#include <memory>
#include <vector>
#include <initializer_list>
#include "point.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Polygon : public std::vector<Point<_Tp>>
    {
        typedef std::vector<Point<_Tp>> base_type;

    public:

        //构造
        constexpr Polygon() noexcept : base_type() {}
        template <typename Iterator> constexpr Polygon(Iterator begin, Iterator end) noexcept : base_type(begin, end) {}
        constexpr Polygon(std::initializer_list<Point<_Tp>> l) noexcept : base_type(l.begin(), l.end()) {}
        template<typename _Tp2> constexpr Polygon(const Polygon<_Tp2>& polygon) noexcept;

        //功能函数
        inline constexpr Polygon move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Polygon rotate(const Point<_Tp>& center, double radian) const noexcept;
        inline constexpr Polygon scale(double ratio) const noexcept;

        //符号重载
        inline constexpr Polygon& operator*=(double c) noexcept;
        inline constexpr Polygon& operator/=(double c);
        template<typename _Tp2> inline constexpr Polygon& operator= (const Polygon<_Tp2>&) noexcept;  //类型转换

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Polygon<_Tp>&, const Polygon<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Polygon<_Tp>&, const Polygon<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Polygon<_Tp> operator*(const Polygon<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Polygon<_Tp> operator*(double, const Polygon<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Polygon<_Tp> operator/(const Polygon<_Tp>&, double);

    template<typename _Tp> using PointSet = Polygon<_Tp>;

}

#include "polygon.inl"