#pragma once

#include <memory>

namespace puma::pina
{
    class ComponentImpl;

    class Component 
    {
    public:

        Component();
        virtual ~Component();
        void enable();
        void disable();
        bool isEnabled() const;

    private:

        std::unique_ptr<ComponentImpl> m_impl;
    };

}