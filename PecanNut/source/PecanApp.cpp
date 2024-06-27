#include "Pecan.h"

// 必须将EntryPoint放在这里，重复嵌套也没用
#include "Runtime/Core/EntryPoint.h"

#include "Sandbox2D.h"

namespace Pecan
{

    class PecanApp : public Application
    {
    public:


        PecanApp() : Application("Pecan App") { PushLayer(new Sandbox2D(GetRenderer())); }

        ~PecanApp() override = default;
    };

    Application* CreateApplication() { return new PecanApp(); }

} // namespace Pecan