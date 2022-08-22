#pragma once

#include <memory>

namespace puma::pina
{
    class SystemImpl;
    class ComponentProvider;
    class EntityProvider;

    class System
    {
    public:

        System();
        virtual ~System();

        virtual void uninit() = 0;

        void enable();
        void disable();
        bool isEnabled() const;

    private:

        std::unique_ptr<SystemImpl> m_impl;
    };
}