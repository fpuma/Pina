#include <internal/system/systemimpl.h>
#include <memory>
#include <pina/system.h>

namespace puma::pina
{

    System::System()
    {
        m_impl = std::make_unique<SystemImpl>();
    }

    System::~System() {}

    void System::onInit()
    {

    }

    void System::onUninit()
    {

    }

    void System::enable()
    {
        m_impl->enable();
    }

    void System::disable()
    {
        m_impl->disable();
    }

    bool System::isEnabled() const
    {
        return m_impl->isEnabled();
    }

}