#pragma once

#include <vector>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

namespace qv
{
    template<typename _Tp>
    class VariantBase
    {
    public:
        VariantBase() noexcept;

        void clear();
        void setValue(const _Tp& value);
        void setValue(const std::vector<_Tp>& values);
        _Tp getValue() const;
        const std::vector<_Tp>& getValues() const;

        bool empty() const;
        size_t length() const;

    protected:
        std::vector<_Tp> m_values;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(m_values);
        }

    };
}

#include "variant_base.inl"