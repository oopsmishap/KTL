#include <ktl_runtime/placement_new.hpp>

#if !defined(__PLACEMENT_NEW_INLINE)
void* CRTCALL operator new(size_t bytes_count, void* ptr) noexcept
{
    (void)bytes_count;
    return ptr;
}
#endif