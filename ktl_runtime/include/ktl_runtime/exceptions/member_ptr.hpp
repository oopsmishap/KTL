#pragma once
#include "../types.hpp"

namespace ktl::crt::exceptions
{
using uintptr_t = int64_t;
using offset_t  = uint32_t;

class member_ptr
{
  public:
    member_ptr(offset_t vbase_offset, offset_t vbtable_ptr_offset, offset_t member_offset) noexcept;

    uintptr_t apply(uintptr_t obj) const noexcept;

  private:
    offset_t m_vbase_offset;
    offset_t m_vbtable_ptr_offset;
    offset_t m_member_offset;
};

} // namespace ktl::crt::exceptions