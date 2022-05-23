#pragma once

namespace rv
{
    template<typename _Tp = double> 
    class Size
    {
    public:

        //构造
        constexpr Size() noexcept;
        constexpr Size(_Tp _width, _Tp _height) noexcept;
        template<typename _Tp2> constexpr Size(const Size<_Tp2>& size) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr _Tp area() const noexcept;

        //符号重载
        inline constexpr Size& operator+=(const Size&) noexcept;
        inline constexpr Size& operator-=(const Size&) noexcept;
        inline constexpr Size& operator*=(double c) noexcept;
        inline constexpr Size& operator/=(double c);
        template<typename _Tp2> inline constexpr Size& operator= (const Size<_Tp2>&) noexcept;   //类型转换

        //核心数据
        _Tp width;
        _Tp height;
    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Size<_Tp>&, const Size<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Size<_Tp>&, const Size<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Size<_Tp> operator+(const Size<_Tp>&, const Size<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Size<_Tp> operator-(const Size<_Tp>&, const Size<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Size<_Tp> operator*(const Size<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Size<_Tp> operator*(double, const Size<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Size<_Tp> operator/(const Size<_Tp>&, double);

}

#include "size.inl"