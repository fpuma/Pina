#pragma once

#include <memory>

namespace puma::pina
{
    class ComponentImpl;

    class Component 
    {
    public:

        friend class ComponentProvider;

        Component();
        virtual ~Component();
        void enable();
        void disable();
        bool isEnabled() const;
        virtual void onEnabled() {}
        virtual void onDisabled() {}
    private:

        std::unique_ptr<ComponentImpl> m_impl;
    };

}