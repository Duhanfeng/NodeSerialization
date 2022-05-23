#include "contours.hpp"
#include "rmath.h"

namespace rv
{
    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr rv::Contours<_Tp>::Contours(const Contours<_Tp2>& contours) noexcept
    {
        size_t _size = contours.size();
        for (size_t i = 0; i < _size; i++)
        {
            this->emplace_back(contours[i]);
        }
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Contours<_Tp>& Contours<_Tp>::operator=(const Contours<_Tp2>& contours) noexcept
    {
        size_t _size = contours.size();
        for (size_t i = 0; i < _size; i++)
        {
            this->emplace_back(contours[i]);
        }
        return *this;
    }

    template<typename _Tp>
    inline constexpr Contours<_Tp> Contours<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        Contours<_Tp> contours;

        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            contours.emplace_back((*this)[i].move(dx, dy));
        }

        return contours;
    }

    template<typename _Tp>
    inline constexpr Contours<_Tp> Contours<_Tp>::rotate(const Point<_Tp>& center, double radian) const noexcept
    {
        Contours<_Tp> contours;

        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            contours.emplace_back((*this)[i].rotate(center, radian));
        }

        return contours;
    }

    template<typename _Tp>
    inline constexpr Contours<_Tp> Contours<_Tp>::scale(double ratio) const noexcept
    {

        return *this * ratio;
    }

    template<typename _Tp>
    inline constexpr Contours<_Tp>& Contours<_Tp>::operator*=(double c) noexcept
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] *= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr Contours<_Tp>& Contours<_Tp>::operator/=(double c)
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] /= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Contours<_Tp>& contours1, const Contours<_Tp>& contours2) noexcept
    {
        if (contours1.size() != contours2.size())
        {
            return false;
        }

        if (contours1.size() == 0)
        {
            return true;
        }

        size_t _size = contours1.size();
        for (size_t i = 0; i < _size; i++)
        {
            if (contours1[i] != contours2[i])
            {
                return false;
            }
        }

        return true;
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Contours<_Tp>& contours1, const Contours<_Tp>& contours2) noexcept
    {
        return !(contours1 == contours2);
    }

    template<typename _Tp>
    inline constexpr const Contours<_Tp> operator*(const Contours<_Tp>& contours, double c) noexcept
    {
        Contours<_Tp> contours2;

        size_t _size = contours.size();
        for (size_t i = 0; i < _size; i++)
        {
            contours2.emplace_back(contours[i] * c);
        }

        return contours2;
    }

    template<typename _Tp>
    inline constexpr const Contours<_Tp> operator*(double c, const Contours<_Tp>& contours) noexcept
    {
        Contours<_Tp> contours2;

        size_t _size = contours.size();
        for (size_t i = 0; i < _size; i++)
        {
            contours2.emplace_back(contours[i] * c);
        }

        return contours2;
    }

    template<typename _Tp>
    inline constexpr const Contours<_Tp> operator/(const Contours<_Tp>& contours, double c)
    {
        Contours<_Tp> contours2;

        size_t _size = contours.size();
        for (size_t i = 0; i < _size; i++)
        {
            contours2.emplace_back(contours[i] / c);
        }

        return contours2;
    }
}
