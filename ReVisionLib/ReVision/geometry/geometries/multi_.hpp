#pragma once

#include <memory>
#include <vector>
#include <initializer_list>

namespace rv
{
    template<typename _Tp>
    class Multi_ : public std::vector<_Tp>
    {
        typedef std::vector<_Tp> base_type;

    public:

        //构造
        constexpr Multi_() noexcept : base_type() {}
        template <typename Iterator> constexpr Multi_(Iterator begin, Iterator end) noexcept : base_type(begin, end) {}
        constexpr Multi_(std::initializer_list<_Tp> l) noexcept : base_type(l.begin(), l.end()) {}
        template<typename _Tp2> constexpr Multi_(const Multi_<_Tp2>& value) noexcept;

        //功能函数

        inline constexpr Multi_<_Tp> scale(double ratio) const noexcept;

        //符号重载
        inline constexpr Multi_& operator*=(double c) noexcept;
        inline constexpr Multi_& operator/=(double c);
        template<typename _Tp2> inline constexpr Multi_& operator= (const Multi_<_Tp2>&) noexcept;  //类型转换

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Multi_<_Tp>&, const Multi_<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Multi_<_Tp>&, const Multi_<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Multi_<_Tp> operator*(const Multi_<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Multi_<_Tp> operator*(double, const Multi_<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Multi_<_Tp> operator/(const Multi_<_Tp>&, double);

}

#include "multi_.inl"