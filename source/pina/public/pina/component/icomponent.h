#pragma once

namespace pina
{
    class IComponent 
    {
    public:
        virtual ~IComponent() {}
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual bool isEnabled() const = 0;
    };
}