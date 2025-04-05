#pragma once

#include "iterator.hpp"
#include "utility.hpp"

namespace ktl
{
template <class ForwardIt, class T, class Predicate>
constexpr bool binary_search(ForwardIt first, ForwardIt last, const T& value, Predicate pred)
{
    auto count{distance(first, last)};

    while (0 < count)
    {
        const auto count_half{count / 2};
        if (auto middle = next(first, count_half); pred(*middle, value))
        {
            first = next(middle);
            count -= count_half + 1;
        }
        else
        {
            count = count_half;
        }
    }
    return (first == last) ? false : *first == value;
}

template <class ForwardIt, class Ty>
constexpr bool binary_search(ForwardIt first, ForwardIt last, const Ty& value)
{
    return binary_search(first, last, value, less<>{});
}

template <class Ty1, class Ty2>
constexpr decltype(auto)(min)(const Ty1& lhs, const Ty2& rhs) noexcept(noexcept(rhs < lhs))
{
    return rhs < lhs ? rhs : lhs;
}

template <class Ty1, class Ty2>
constexpr decltype(auto)(max)(const Ty1& lhs, const Ty2& rhs) noexcept(noexcept(lhs < rhs))
{
    return lhs < rhs ? rhs : lhs;
}
} // namespace ktl