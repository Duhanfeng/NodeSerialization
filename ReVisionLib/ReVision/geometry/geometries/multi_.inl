#include "multi_.hpp"
#include "ReVision/rmath.h"

namespace rv
{
    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr rv::Multi_<_Tp>::Multi_(const Multi_<_Tp2>& value) noexcept
    {
        size_t _size = value.size();
        for (size_t i = 0; i < _size; i++)
        {
            this->emplace_back(value[i]);
        }
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Multi_<_Tp>& Multi_<_Tp>::operator=(const Multi_<_Tp2>& value) noexcept
    {
        this->clear();
        size_t _size = value.size();
        for (size_t i = 0; i < _size; i++)
        {
            this->emplace_back(value[i]);
        }
        return *this;
    }

    template<typename _Tp>
    inline constexpr Multi_<_Tp> Multi_<_Tp>::scale(double ratio) const noexcept
    {

        return *this * ratio;
    }

    template<typename _Tp>
    inline constexpr Multi_<_Tp>& Multi_<_Tp>::operator*=(double c) noexcept
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] *= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr Multi_<_Tp>& Multi_<_Tp>::operator/=(double c)
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] /= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Multi_<_Tp>& runs1, const Multi_<_Tp>& runs2) noexcept
    {
        if (runs1.size() != runs2.size())
        {
            return false;
        }

        if (runs1.size() == 0)
        {
            return true;
        }

        size_t _size = runs1.size();
        for (size_t i = 0; i < _size; i++)
        {
            if (runs1[i] != runs2[i])
            {
                return false;
            }
        }

        return true;
    }

    template<typename _Tp>
    inline constexpr bool operator!=(const Multi_<_Tp>& runs1, const Multi_<_Tp>& runs2) noexcept
    {
        return !(runs1 == runs2);
    }

    template<typename _Tp>
    inline constexpr const Multi_<_Tp> operator*(const Multi_<_Tp>& value, double c) noexcept
    {
        Multi_<_Tp> runs2;

        size_t _size = value.size();
        for (size_t i = 0; i < _size; i++)
        {
            runs2.emplace_back(value[i] * c);
        }

        return runs2;
    }

    template<typename _Tp>
    inline constexpr const Multi_<_Tp> operator*(double c, const Multi_<_Tp>& value) noexcept
    {
        Multi_<_Tp> runs2;

        size_t _size = value.size();
        for (size_t i = 0; i < _size; i++)
        {
            runs2.emplace_back(value[i] * c);
        }

        return runs2;
    }

    template<typename _Tp>
    inline constexpr const Multi_<_Tp> operator/(const Multi_<_Tp>& value, double c)
    {
        Multi_<_Tp> runs2;

        size_t _size = value.size();
        for (size_t i = 0; i < _size; i++)
        {
            runs2.emplace_back(value[i] / c);
        }

        return runs2;
    }
}
