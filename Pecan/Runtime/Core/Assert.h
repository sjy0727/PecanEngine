#pragma once

#include "Runtime/Core/Base.h"
#include "Runtime/Core/Log.h"

#ifdef PC_ENABLE_ASSERTS
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the
// default message
#    define PC_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
        { \
            if (!(check)) \
            { \
                PC##type##ERROR(msg, __VA_ARGS__); \
                PC_DEBUGBREAK(); \
            } \
        }
#    define PC_INTERNAL_ASSERT_WITH_MSG(type, check, ...) \
        PC_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#    define PC_INTERNAL_ASSERT_NO_MSG(type, check) \
        PC_INTERNAL_ASSERT_IMPL(type, \
                                check, \
                                "Assertion '{0}' failed at {1}:{2}", \
                                PC_STRINGIFY_MACRO(check), \
                                std::filesystem::path(__FILE__).filename().string(), \
                                __LINE__)

#    define PC_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#    define PC_INTERNAL_ASSERT_GET_MACRO(...) \
        PC_EXPAND_MACRO( \
            PC_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, PC_INTERNAL_ASSERT_WITH_MSG, PC_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#    define PC_ASSERT(...) PC_EXPAND_MACRO(PC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#    define PC_CORE_ASSERT(...) PC_EXPAND_MACRO(PC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#    define PC_ASSERT(...)
#    define PC_CORE_ASSERT(...)
#endif
