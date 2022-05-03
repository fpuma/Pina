#pragma once

#include <pina/system/isystem.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace puma
{
    class ISystemProvider : public UniqueRealizationContainer<ISystem>, public NonCopyable
    {
    public:
        virtual ~ISystemProvider(){}

        virtual void updateSystemsProperties() = 0;
    };
}