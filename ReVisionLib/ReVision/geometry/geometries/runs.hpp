#pragma once

#include <memory>
#include <vector>
#include <initializer_list>
#include "point.hpp"
#include "run.hpp"

namespace rv
{
    template<typename _Tp = short>
    class Runs
    {
    public:

        //构造
        constexpr Runs() noexcept;
        template<typename _Tp2> constexpr Runs(const Runs<_Tp2>& polygon) noexcept;

        //功能函数
        inline constexpr size_t size() const noexcept;
        inline constexpr Runs move(_Tp dx, _Tp dy) const noexcept;
        inline constexpr Runs scale(double ratio) const noexcept;
        inline constexpr void readFormImage(unsigned char* data, int width, int height);    //备注:要求data必须是连续的内存

        //符号重载
        inline constexpr Runs& operator*=(double c) noexcept;
        inline constexpr Runs& operator/=(double c);
        template<typename _Tp2> inline constexpr Runs& operator= (const Runs<_Tp2>&) noexcept;  //类型转换

        //核心数据
        std::vector<_Tp> r;
        std::vector<_Tp> cb;
        std::vector<_Tp> ce;

    };

    //符号重载
    template<typename _Tp> inline constexpr bool operator==(const Runs<_Tp>&, const Runs<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr bool operator!=(const Runs<_Tp>&, const Runs<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Runs<_Tp> operator*(const Runs<_Tp>&, double) noexcept;
    template<typename _Tp> inline constexpr const Runs<_Tp> operator*(double, const Runs<_Tp>&) noexcept;
    template<typename _Tp> inline constexpr const Runs<_Tp> operator/(const Runs<_Tp>&, double);

}

#include "runs.inl"