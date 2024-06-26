#include "pcpch.h"

#include "Runtime/Core/Layer.h"

namespace Pecan
{

    Layer::Layer(const std::string& name) : m_DebugName(name) {}

    Layer::~Layer() = default;

} // namespace LiteGine