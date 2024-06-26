#ifndef PECANENGINE_BASE_H
#define PECANENGINE_BASE_H

#include <memory>

#define PC_EXPAND_MACRO(x) x
#define PC_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define PC_BIND_EVENT_FN(fn) \
    [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Pecan
{

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

} // namespace Pecan

#endif // PECANENGINE_BASE_H
