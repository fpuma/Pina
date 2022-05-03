#pragma once

#include <pina/entity/entity.h>
#include <pina/component/icomponent.h>
#include <pina/provider/iprovider.h>
#include <utils/containers/mappedrealizationcontainer.h>

namespace puma
{
    class IComponentProvider : public MappedRealizationContainer<Entity, IComponent>, public IProvider
    {
    public:
        virtual ~IComponentProvider(){}
    };
}