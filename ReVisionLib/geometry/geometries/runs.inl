#include "runs.hpp"
#include "rmath.h"

namespace rv
{
    template<typename _Tp>
    constexpr rv::Runs<_Tp>::Runs() noexcept : r(), cb(), ce()
    {

    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr rv::Runs<_Tp>::Runs(const Runs<_Tp2>& runs) noexcept
    {
        size_t _size = runs.r.size();
        for (size_t i = 0; i < _size; i++)
        {
            r->emplace_back(_Tp(runs.r[i]));
            cb->emplace_back(_Tp(runs.cb[i]));
            ce->emplace_back(_Tp(runs.ce[i]));
        }
    }

    template<typename _Tp>
    template<typename _Tp2>
    inline constexpr Runs<_Tp>& Runs<_Tp>::operator=(const Runs<_Tp2>& runs) noexcept
    {
        this->r.clear();
        this->cb.clear();
        this->ce.clear();
        size_t _size = runs.r.size();
        for (size_t i = 0; i < _size; i++)
        {
            r->emplace_back(_Tp(runs.r[i]));
            cb->emplace_back(_Tp(runs.cb[i]));
            ce->emplace_back(_Tp(runs.ce[i]));
        }
        return *this;
    }

    template<typename _Tp>
    inline constexpr size_t Runs<_Tp>::size() const noexcept
    {
        return r.size();
    }

    template<typename _Tp>
    inline constexpr Runs<_Tp> Runs<_Tp>::move(_Tp dx, _Tp dy) const noexcept
    {
        Runs<_Tp> runs;

        size_t _size = r.size()();
        for (size_t i = 0; i < _size; i++)
        {
            runs.r.emplace_back(r[i] + dy);
            runs.cb.emplace_back(cb[i] + dx);
            runs.ce.emplace_back(ce[i] + dx);
        }

        return runs;
    }

    template<typename _Tp>
    inline constexpr Runs<_Tp> Runs<_Tp>::scale(double ratio) const noexcept
    {

        return *this * ratio;
    }

    template<typename _Tp>
    inline constexpr void Runs<_Tp>::readFormImage(unsigned char* data, int width, int height)
    {
        r.clear();
        cb.clear();
        ce.clear();

        for (int _r = 0; _r < height; _r++)
        {
            bool isStart = false;

            for (int _c = 0; _c < width; _c++)
            {
                if (!isStart)
                {
                    if (*data != 0)
                    {
                        isStart = true;
                        r.emplace_back(_Tp(_r));
                        cb.emplace_back(_Tp(_c));
                    }
                }
                else
                {
                    //如果已经开始,而当前为0,则认为已经结束
                    if (*data == 0)
                    {
                        isStart = false;
                        ce.emplace_back(_Tp(_c - 1));
                    }
                }

                data++;
            }

            //如果查找到末尾,则保存末尾
            if (isStart)
            {
                ce.emplace_back(_Tp(width - 1));
            }
        }

    }

    template<typename _Tp>
    inline constexpr Runs<_Tp>& Runs<_Tp>::operator*=(double c) noexcept
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] *= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr Runs<_Tp>& Runs<_Tp>::operator/=(double c)
    {
        size_t _size = this->size();
        for (size_t i = 0; i < _size; i++)
        {
            (*this)[i] /= c;
        }

        return *this;
    }

    template<typename _Tp>
    inline constexpr bool operator==(const Runs<_Tp>& runs1, const Runs<_Tp>& runs2) noexcept
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
    inline constexpr bool operator!=(const Runs<_Tp>& runs1, const Runs<_Tp>& runs2) noexcept
    {
        return !(runs1 == runs2);
    }

    template<typename _Tp>
    inline constexpr const Runs<_Tp> operator*(const Runs<_Tp>& runs, double c) noexcept
    {
        Runs<_Tp> runs2;

        size_t _size = runs.size();
        for (size_t i = 0; i < _size; i++)
        {
            runs2.r.emplace_back(runs.r[i] * c);
            runs2.cb.emplace_back(runs.cb[i] * c);
            runs2.ce.emplace_back(runs.ce[i] * c);
        }

        return runs2;
    }

    template<typename _Tp>
    inline constexpr const Runs<_Tp> operator*(double c, const Runs<_Tp>& runs) noexcept
    {
        Runs<_Tp> runs2;

        size_t _size = runs.size();
        for (size_t i = 0; i < _size; i++)
        {
            runs2.r.emplace_back(runs.r[i] * c);
            runs2.cb.emplace_back(runs.cb[i] * c);
            runs2.ce.emplace_back(runs.ce[i] * c);
        }

        return runs2;
    }

    template<typename _Tp>
    inline constexpr const Runs<_Tp> operator/(const Runs<_Tp>& runs, double c)
    {
        Runs<_Tp> runs2;

        size_t _size = runs.size();
        for (size_t i = 0; i < _size; i++)
        {
            runs2.r.emplace_back(runs.r[i] / c);
            runs2.cb.emplace_back(runs.cb[i] / c);
            runs2.ce.emplace_back(runs.ce[i] / c);
        }

        return runs2;
    }
}
