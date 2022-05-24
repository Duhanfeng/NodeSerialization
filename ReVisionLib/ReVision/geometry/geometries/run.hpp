#pragma once

namespace rv
{
    template<typename _Tp = short>
    class Run
    {
    public:

        //构造
        constexpr Run() noexcept;
        constexpr Run(_Tp _r, _Tp _cb, _Tp _ce) noexcept;
        template<typename _Tp2> constexpr Run(const Run<_Tp2>& run) noexcept;

        //功能函数
        inline constexpr bool isNull() const noexcept;
        inline constexpr Run move(_Tp dx, _Tp dy) const noexcept;

        //符号重载
        inline constexpr Run& operator*=(double c) noexcept;
        inline constexpr Run& operator/=(double c);
        template<typename _Tp2> inline constexpr Run& operator= (const Run<_Tp2>&) noexcept;  //类型转换

        //核心数据
        _Tp r;  //游程行数(row)
        _Tp cb; //开始点
        _Tp ce; //结束点

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Run<_Tp>&, const Run<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Run<_Tp>&, const Run<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Run<_Tp> operator*(const Run<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Run<_Tp> operator*(double, const Run<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Run<_Tp> operator/(const Run<_Tp>&, double);

}

#include "run.inl"