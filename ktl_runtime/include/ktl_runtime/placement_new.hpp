#pragma once
#include "types.hpp"
#include "crt_attributes.hpp"

#if !defined(__PLACEMENT_NEW_INLINE)
void* CRTCALL operator new(size_t bytes_count, void* ptr) noexcept;
#endif