#pragma once

#include "Runtime/Core/Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
// 先spdlog.h再fmt/ostr.h
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace Pecan
{
    class Log
    {
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;

    public:
        // Log();
        // ~Log();

        static void Init();

        inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    };
} // namespace Pecan

// Core日志宏
#define PC_CORE_ERROR(...) ::Pecan::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PC_CORE_WARN(...) ::Pecan::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PC_CORE_INFO(...) ::Pecan::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PC_CORE_TRACE(...) ::Pecan::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PC_CORE_CRITICAL(...) ::Pecan::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client日志宏
#define PC_ERROR(...) ::Pecan::Log::GetClientLogger()->error(__VA_ARGS__)
#define PC_WARN(...) ::Pecan::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PC_INFO(...) ::Pecan::Log::GetClientLogger()->info(__VA_ARGS__)
#define PC_TRACE(...) ::Pecan::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PC_CRITICAL(...) ::Pecan::Log::GetClientLogger()->critical(__VA_ARGS__)
