#include <ktl_runtime/types.hpp>
#include <ktl_runtime/exceptions/x64/throw.hpp>

namespace ktl::crt::exceptions::x64
{
dispatcher_context make_context(symbol* cookie, throw_frame& frame, const frame_walk_pdata& pdata) noexcept
{
    dispatcher_context ctx{};
    ctx.image_base  = pdata.image_base();
    ctx.pdata       = &pdata;
    ctx.throw_frame = &frame;
    ctx.cookie      = cookie;
    return ctx;
}
} // namespace ktl::crt::exceptions::x64