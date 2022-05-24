#include "run.hpp"
#include "ReVision/rmath.h"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Run<_Tp>::Run() noexcept : r(_Tp(0)), cb(_Tp(0)), ce(_Tp(0))
    {
    }

    template<typename _Tp>
    inline constexpr rv::Run<_Tp>::Run(_Tp _r, _Tp _cb, _Tp _ce) noexcept : r(_r), cb(_cb), ce(_ce)
    {
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Run<_Tp>::Run(const Run<_Tp2>& run) noexcept
    {
        r = _Tp(run.r);
        cb = _Tp(run.cb);
        ce = _Tp(run.ce);
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Run<_Tp>& Run<_Tp>::operator=(const Run<_Tp2>& run) noexcept
    {
        r = _Tp(run.r);
        cb = _Tp(run.cb);
        ce = _Tp(run.ce);
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool Run<_Tp>::isNull() const noexcept
    {
        return isNull(r) && isNull(cb) && isNull(ce);
    }

    template<typename _Tp>
    inline constexpr Run<_Tp> Run<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        return Run<_Tp>(r + dy, cb + dx, ce + dx);
    }

    template<typename _Tp>
    inline constexpr Run<_Tp>& Run<_Tp>::operator*=(double c) noexcept
    {
        r *= c;
        cb *= c;
        ce *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Run<_Tp>& Run<_Tp>::operator/=(double c)
    {
        r /= c;
        cb /= c;
        ce /= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Run<_Tp>& run1, const Run<_Tp>& run2) noexcept
    {
        return fuzzyCompare(run1.r, run2.r) &&
            fuzzyCompare(run1.cb, run2.cb) &&
            fuzzyCompare(run1.ce, run2.ce);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Run<_Tp>& run1, const Run<_Tp>& run2) noexcept
    {
        return !(run1 == run2);
    }

    template<typename _Tp>
    inline constexpr const Run<_Tp> operator*(const Run<_Tp>& run, double c) noexcept
    {
        return Run<_Tp>(run.r * c, run.cb * c, run.ce * c);
    }

    template<typename _Tp>
    inline constexpr const Run<_Tp> operator*(double c, const Run<_Tp>& run) noexcept
    {
        return Run<_Tp>(run.r * c, run.cb * c, run.ce * c);
    }

    template<typename _Tp>
    inline constexpr const Run<_Tp> operator/(const Run<_Tp>& run, double c)
    {
        return Run<_Tp>(run.r / c, run.cb / c, run.ce / c);
    }

}