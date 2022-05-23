#include "variant_base.h"

namespace qv
{
    template<typename _Tp>
    inline VariantBase<_Tp>::VariantBase() noexcept :
        m_values()
    {
    }

    template<typename _Tp>
    inline void VariantBase<_Tp>::clear()
    {
        m_values.clear();
    }

    template<typename _Tp>
    inline void VariantBase<_Tp>::setValue(const _Tp& value)
    {
        m_values.clear();
        m_values.push_back(value);
    }

    template<typename _Tp>
    inline void VariantBase<_Tp>::setValue(const std::vector<_Tp>& values)
    {
        m_values.clear();
        m_values = values;
    }

    template<typename _Tp>
    inline _Tp VariantBase<_Tp>::getValue() const
    {
        if (empty())
        {
            return _Tp();
        }

        return m_values[0];
    }

    template<typename _Tp>
    inline const std::vector<_Tp>& VariantBase<_Tp>::getValues() const
    {
        return m_values;
    }

    template<typename _Tp>
    inline bool VariantBase<_Tp>::empty() const
    {
        return m_values.empty();
    }

    template<typename _Tp>
    inline size_t VariantBase<_Tp>::length() const
    {
        return m_values.size();
    }

}
