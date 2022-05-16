#pragma once

#include <pina/system/isystem.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace pina
{
    class ISystemProvider : public puma::UniqueRealizationContainer<ISystem>, public puma::NonCopyable
    {
    public:
        virtual ~ISystemProvider(){}

        void uninit()
        {
            traverse([](ISystem* sys) { sys->uninit(); });
        }
    };
}