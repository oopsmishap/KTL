#include <dynamic_init.hpp>
#include <exception_dispatcher.hpp>
#include <floating_point.hpp>
#include <heap.hpp>
#include <irql.hpp>
#include <placement_new.hpp>
#include <preload_init.hpp>
#include <test_runner.hpp>

#include <ktl/runtime.hpp>
#include <ktl/fmt.hpp>
#include <ktl/chrono.hpp>
#include <ktl/string.hpp>

#include <ntddk.h>

using namespace ktl;

void run_tests()
{
    tests::runner tr;

    RUN_TEST(tr, tests::dynamic_init::verify_initializers);
    RUN_TEST(tr, tests::preload_init::verify_initializers);

    RUN_TEST(tr, tests::placement_new::construct_on_buffer);
    RUN_TEST(tr, tests::placement_new::construct_after_destroying);
    RUN_TEST(tr, tests::placement_new::construct_with_launder);

    RUN_TEST(tr, tests::floating_point::validate_fltused);
    RUN_TEST(tr, tests::floating_point::perform_arithmetic_operations);

    RUN_TEST(tr, tests::heap::alloc_and_free);
    RUN_TEST(tr, tests::heap::alloc_and_free_noexcept);

    RUN_TEST(tr, tests::irql::current);
    RUN_TEST(tr, tests::irql::raise_and_lower);
    RUN_TEST(tr, tests::irql::less_or_equal);

    RUN_TEST(tr, tests::exception_dispatcher::throw_directly);
    RUN_TEST(tr, tests::exception_dispatcher::throw_in_nested_call);
    RUN_TEST(tr, tests::exception_dispatcher::throw_on_array_init);
    RUN_TEST(tr, tests::exception_dispatcher::throw_in_new_expression);
    RUN_TEST(tr, tests::exception_dispatcher::throw_at_high_irql);
    RUN_TEST(tr, tests::exception_dispatcher::catch_by_value);
    RUN_TEST(tr, tests::exception_dispatcher::catch_by_base_ref);
    RUN_TEST(tr, tests::exception_dispatcher::catch_by_base_ptr);
}

TIME_FIELDS get_current_time() noexcept
{
    const auto    current_time{chrono::system_clock::now().time_since_epoch().count()};
    LARGE_INTEGER native_time;
    native_time.QuadPart = static_cast<long long>(current_time);
    TIME_FIELDS time_fields;
    RtlTimeToTimeFields(addressof(native_time), addressof(time_fields));
    return time_fields;
}

EXTERN_C NTSTATUS
driver_entry([[maybe_unused]] DRIVER_OBJECT* driver_object, [[maybe_unused]] UNICODE_STRING* registry_path) noexcept
try
{
    const auto time{get_current_time()};

    auto str{format(
        FMT_COMPILE(L"[{:02}-{:02}-{:04} {:02}:{:02}:{:02}.{:03}][{}]"),
        time.Day,
        time.Month,
        time.Year,
        time.Hour,
        time.Minute,
        time.Second,
        time.Milliseconds,
        L"KTL Test Driver"
    )};
    DbgPrint("%wZ\n", str.raw_str());

    run_tests();

    return STATUS_SUCCESS;
}
catch (const exception& exc)
{
    DbgPrint("Unhandled exception caught: %s with code %x\n", exc.what(), exc.code());
    return exc.code();
}