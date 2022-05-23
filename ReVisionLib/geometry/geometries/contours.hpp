#pragma once

#include <memory>
#include <vector>
#include <initializer_list>
#include "polygon.hpp"

namespace rv
{
    template<typename _Tp = double>
    class Contours : public std::vector<Polygon<_Tp>>
    {
        typedef std::vector<Polygon<_Tp>> base_type;

    public:

        //构造
        constexpr Contours() noexcept : base_type() {}
        template <typename Iterator> constexpr Contours(Iterator begin, Iterator end) noexcept : base_type(begin, end) {}
        constexpr Contours(std::initializer_list<Polygon<_Tp>> l) noexcept : base_type(l.begin(), l.end()) {}
        template<typename _Tp2> constexpr Contours(const Contours<_Tp2>& contours) noexcept;

        //功能函数
        inline constexpr Contours move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Contours rotate(const Point<_Tp>& center, double radian) const noexcept;
        inline constexpr Contours scale(double ratio) const noexcept;

        //符号重载
        inline constexpr Contours& operator*=(double c) noexcept;
        inline constexpr Contours& operator/=(double c);
        template<typename _Tp2> inline constexpr Contours& operator= (const Contours<_Tp2>&) noexcept;  //类型转换

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Contours<_Tp>&, const Contours<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Contours<_Tp>&, const Contours<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Contours<_Tp> operator*(const Contours<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Contours<_Tp> operator*(double, const Contours<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Contours<_Tp> operator/(const Contours<_Tp>&, double);

}

#include "contours.inl"