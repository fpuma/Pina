#pragma once
#include <pina/provider/iprovider.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace puma
{
    class IProviderContainer : public UniqueRealizationContainer<IProvider>, public NonCopyable
    {
    public:

        virtual ~IProviderContainer(){}
    };
}