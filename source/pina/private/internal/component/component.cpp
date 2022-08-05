#pragma once

#include <internal/component/componentimpl.h>
#include <pina/component.h>
#include <memory>

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
    }

    void Component::disable()
    {
        m_impl->disable();
    }

    bool Component::isEnabled() const
    {
        return m_impl->isEnabled();
    }

}