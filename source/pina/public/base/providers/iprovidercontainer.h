#pragma once
#include <base/providers/iprovider.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace puma
{
    class IProviderContainer : public UniqueRealizationContainer<IProvider>, public NonCopyable
    {
    public:

        virtual ~IProviderContainer(){}
    };
}