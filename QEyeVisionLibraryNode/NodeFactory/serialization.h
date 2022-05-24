#pragma once

#include <string>

namespace qv
{
    template<typename _Tp> inline constexpr bool serializeText(const _Tp& data, const std::string& file) noexcept;
    template<typename _Tp> inline constexpr bool deserializeText(_Tp& data, const std::string& file) noexcept;

    template<typename _Tp> inline constexpr bool serializeBin(const _Tp& data, const std::string& file) noexcept;
    template<typename _Tp> inline constexpr bool deserializeBin(_Tp& data, const std::string& file) noexcept;

    template<typename _Tp> inline constexpr bool serializeXml(const _Tp& data, const std::string& file) noexcept;
    template<typename _Tp> inline constexpr bool deserializeXml(_Tp& data, const std::string& file) noexcept;
}

#include "serialization.inl"