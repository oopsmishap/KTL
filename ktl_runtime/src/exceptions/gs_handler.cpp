#include <ktl_runtime/bugcheck.hpp>
#include <ktl_runtime/exceptions/frame_handler.hpp>
#include <ktl_runtime/exceptions/x64/throw.hpp>

EXTERN_C void __GSHandlerCheckCommon(
    ktl::byte* frame_ptr, ktl::crt::exceptions::x64::dispatcher_context* ctx, const void* handler_data
) noexcept;

EXTERN_C [[noreturn]] void report_security_check_failure()
{
    ktl::crt::set_termination_context({ktl::crt::BugCheckReason::BufferSecurityCheckFailure});
    ktl::terminate();
}

namespace ktl::crt::exceptions::x64
{
void gs_handler(byte* frame_ptr, dispatcher_context* dispatcher_context)
{
    const auto* handler_data{static_cast<const gs_handler_data*>(dispatcher_context->extra_data)};
    __GSHandlerCheckCommon(frame_ptr, dispatcher_context, addressof(handler_data->aligned_base_offset));
}
} // namespace ktl::crt::exceptions::x64