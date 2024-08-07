#pragma once

#include "Runtime/Core/Application.h"
#include "Runtime/Core/Base.h"
#include "Runtime/Core/Log.h"

// #ifdef LG_PLATFORM_MACOS

// extern Pecan::Application* Pecan::CreateApplication();

int main(int argc, char* argv[])
{
    Pecan::Log::Init();
    // LiteGine::Log::GetCoreLogger()->warn("Initialized log!");
    // LiteGine::Log::GetClientLogger()->info("Hello!");
    // LG_CORE_WARN("Initialized Logger!");

    PC_PROFILE_BEGIN_SESSION("Startup", "PecanProfile-Startup.json");
    auto app = Pecan::CreateApplication();
    PC_PROFILE_END_SESSION();

    // int magicNumber = 666;
    // LG_INFO("Sandbox start! magicNumber={0}", magicNumber);

    PC_PROFILE_BEGIN_SESSION("Runtime", "PecanProfile-Runtime.json");
    app->Run();
    PC_PROFILE_END_SESSION();

    PC_PROFILE_BEGIN_SESSION("Shutdown", "PecanProfile-Shutdown.json");
    delete app;
    PC_PROFILE_END_SESSION();

    return 0;
}
