#include "polygon.hpp"
#include "ReVision/rmath.h"

namespace rv
{
    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr rv::Polygon<_Tp>::Polygon(const Polygon<_Tp2>& polygon) noexcept
    {
        size_t _size = polygon.size();
        for (size_t i = 0; i < _size; i++)
        {
            this->emplace_back(polygon[i]);
        }
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Polygon<_Tp>& Polygon<_Tp>::operator=(const Polygon<_Tp2>& polygon) noexcept
    {
        size_t _size = polygon.size();
        for (size_t i = 0; i < _size; i++)
        {
            this->emplace_back(polygon[i]);
        }
        return *this;
    }

    template<typename _Tp>
    inline constexpr Polygon<_Tp> Polygon<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        Polygon<_Tp> polygon;

        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            polygon.emplace_back(Point<_Tp>((*this)[i].x + dx, (*this)[i].y + dy));
        }

        return polygon;
    }

    template<typename _Tp>
    inline constexpr Polygon<_Tp> Polygon<_Tp>::rotate(const Point<_Tp>& center, double radian) const noexcept
    {
        Polygon<_Tp> polygon;

        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            polygon.emplace_back((*this)[i].rotate(center, radian));
        }

        return polygon;
    }

    template<typename _Tp>
    inline constexpr Polygon<_Tp> Polygon<_Tp>::scale(double ratio) const noexcept
    {

        return *this * ratio;
    }

    template<typename _Tp>
    inline constexpr Polygon<_Tp>& Polygon<_Tp>::operator*=(double c) noexcept
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] *= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr Polygon<_Tp>& Polygon<_Tp>::operator/=(double c)
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] /= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Polygon<_Tp>& polygon1, const Polygon<_Tp>& polygon2) noexcept
    {
        if (polygon1.size() != polygon2.size())
        {
            return false;
        }

        if (polygon1.size() == 0)
        {
            return true;
        }

        size_t _size = polygon1.size();
        for (size_t i = 0; i < _size; i++)
        {
            if (polygon1[i] != polygon2[i])
            {
                return false;
            }
        }

        return true;
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Polygon<_Tp>& polygon1, const Polygon<_Tp>& polygon2) noexcept
    {
        return !(polygon1 == polygon2);
    }

    template<typename _Tp>
    inline constexpr const Polygon<_Tp> operator*(const Polygon<_Tp>& polygon, double c) noexcept
    {
        Polygon<_Tp> polygon2;

        size_t _size = polygon.size();
        for (size_t i = 0; i < _size; i++)
        {
            polygon2.emplace_back(polygon[i] * c);
        }

        return polygon2;
    }

    template<typename _Tp>
    inline constexpr const Polygon<_Tp> operator*(double c, const Polygon<_Tp>& polygon) noexcept
    {
        Polygon<_Tp> polygon2;

        size_t _size = polygon.size();
        for (size_t i = 0; i < _size; i++)
        {
            polygon2.emplace_back(polygon[i] * c);
        }

        return polygon2;
    }

    template<typename _Tp>
    inline constexpr const Polygon<_Tp> operator/(const Polygon<_Tp>& polygon, double c)
    {
        Polygon<_Tp> polygon2;

        size_t _size = polygon.size();
        for (size_t i = 0; i < _size; i++)
        {
            polygon2.emplace_back(polygon[i] / c);
        }

        return polygon2;
    }
}
