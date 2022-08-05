#pragma once

namespace puma::pina
{
    class ComponentImpl 
    {
    public:

        void enable() { m_enabled = true; }
        void disable() { m_enabled = false; }
        bool isEnabled() const { return m_enabled; }

    private:

        bool m_enabled = true;
    };

}