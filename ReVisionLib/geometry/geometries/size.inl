#include "size.hpp"
#include "rmath.h"

namespace rv
{
    template<typename _Tp>
    inline constexpr rv::Size<_Tp>::Size() noexcept : width(_Tp(0)), height(_Tp(0))
    {
    }

    template<typename _Tp>
    inline constexpr rv::Size<_Tp>::Size(_Tp _width, _Tp _height) noexcept : width(_width), height(_height)
    {
    }

    template<typename _Tp>
    inline constexpr bool rv::Size<_Tp>::isNull() const noexcept
    {
        return isNull(width) && isNull(height);
    }

    template<typename _Tp>
    inline constexpr _Tp Size<_Tp>::area() const noexcept
    {
        return _Tp(width * height);
    }

    template<typename _Tp>
    inline constexpr Size<_Tp>& Size<_Tp>::operator+=(const Size& size) noexcept
    {
        width += size.width;
        height += size.height;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Size<_Tp>& Size<_Tp>::operator-=(const Size& size) noexcept
    {
        width -= size.width;
        height -= size.height;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Size<_Tp>& Size<_Tp>::operator*=(double c) noexcept
    {
        width *= c;
        height *= c;
        return *this;
    }

    template<typename _Tp>
    inline constexpr Size<_Tp>& Size<_Tp>::operator/=(double c)
    {
        width /= c;
        height /= c;
        return *this;
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Size<_Tp>::Size(const Size<_Tp2>& size) noexcept
    {
        width = _Tp(size.width);
        height = _Tp(size.height);
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Size<_Tp>& Size<_Tp>::operator=(const Size<_Tp2>& size) noexcept
    {
        width = _Tp(size.width);
        height = _Tp(size.height);
        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Size<_Tp>& size1, const Size<_Tp>& size2) noexcept
    {
        return fuzzyCompare(size1.width, size2.width) && fuzzyCompare(size1.height, size2.height);
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Size<_Tp>& size1, const Size<_Tp>& size2) noexcept
    {
        return !fuzzyCompare(size1.width, size2.width) || !fuzzyCompare(size1.height, size2.height);
    }

    template<typename _Tp>
    inline constexpr const Size<_Tp> operator+(const Size<_Tp>& size1, const Size<_Tp>& size2) noexcept
    {
        return Size<_Tp>(size1.width + size2.width, size1.height + size2.height);
    }

    template<typename _Tp>
    inline constexpr const Size<_Tp> operator-(const Size<_Tp>& size1, const Size<_Tp>& size2) noexcept
    {
        return Size<_Tp>(size1.width - size2.width, size1.height - size2.height);
    }

    template<typename _Tp>
    inline constexpr const Size<_Tp> operator*(const Size<_Tp>& size, double c) noexcept
    {
        return Size<_Tp>(size.width * c, size.height * c);
    }

    template<typename _Tp>
    inline constexpr const Size<_Tp> operator*(double c, const Size<_Tp>& size) noexcept
    {
        return Size<_Tp>(size.width * c, size.height * c);
    }

    template<typename _Tp>
    inline constexpr const Size<_Tp> operator/(const Size<_Tp>& size, double c)
    {
        return Size<_Tp>(size.width / c, size.height / c);
    }

}