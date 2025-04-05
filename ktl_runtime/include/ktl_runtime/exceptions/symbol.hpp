#pragma once
#include "../types.hpp"

namespace ktl::crt::exceptions
{
struct symbol
{
    operator const byte*() const noexcept
    {
        return reinterpret_cast<const byte*>(this);
    }

    operator uintptr_t() const noexcept
    {
        return reinterpret_cast<uintptr_t>(this);
    }
};
} // namespace ktl::crt::exceptions