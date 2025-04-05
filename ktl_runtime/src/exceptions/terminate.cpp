#include <ktl_runtime/bugcheck.hpp>

EXTERN_C [[noreturn]] void __std_terminate()
{
    ktl::terminate();
}