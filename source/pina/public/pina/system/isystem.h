#pragma once

#include <utils/noncopyable.h>

namespace pina
{
    class ISystem : public puma::NonCopyable
    {
    public:

        virtual ~ISystem() {}

        virtual void uninit() = 0;
    };
}