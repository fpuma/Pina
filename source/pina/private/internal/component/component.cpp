#include <internal/component/componentimpl.h>
#include <memory>
#include <pina/component.h>

namespace puma::pina
{

    Component::Component()
    {
        m_impl = std::make_unique<ComponentImpl>();
    }

    Component::~Component() {}

    void Component::enable()
    {
        m_impl->enable();
        onEnabled();
    }

    void Component::disable()
    {
        m_impl->disable();
        onDisabled();
    }

    bool Component::isEnabled() const
    {
        return m_impl->isEnabled();
    }

}