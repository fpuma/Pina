#pragma once

#include <base/entity.h>
#include <base/icomponent.h>
#include <base/providers/iprovider.h>
#include <utils/containers/mappedrealizationcontainer.h>

namespace puma
{
    class IComponentProvider : public MappedRealizationContainer<Entity, IComponent>, public IProvider
    {
    public:
        virtual ~IComponentProvider(){}
    };
}