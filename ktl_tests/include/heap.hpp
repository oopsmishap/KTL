#pragma once
#include <ktl/types.hpp>
#include <ktl/heap.hpp>

namespace tests::heap
{
static constexpr ktl::crt::pool_tag_t POOL_TAG{'paeH'};

static_assert(ktl::crt::DEFAULT_HEAP_TAG == ktl::crt::KTL_HEAP_TAG);
static_assert(ktl::crt::MEMORY_PAGE_SIZE == PAGE_SIZE);
static_assert(ktl::crt::CACHE_LINE_SIZE == SYSTEM_CACHE_ALIGNMENT_SIZE);
static_assert(static_cast<size_t>(ktl::crt::XMM_ALIGNMENT) >= 16);

#if defined(_M_X64)
static_assert(static_cast<size_t>(ktl::crt::DEFAULT_ALLOCATION_ALIGNMENT) == 16);
#elif defined(_M_IX86)
static_assert(static_cast<size_t>(ktl::crt::DEFAULT_ALLOCATION_ALIGNMENT) == 8);
#else
#error Unsupported platform
#endif

void alloc_and_free();
void alloc_and_free_noexcept();
} // namespace tests::heap
