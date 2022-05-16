#pragma once

#include <pina/entity/entity.h>
#include <pina/component/icomponent.h>
#include <utils/containers/mappedrealizationcontainer.h>
#include <utils/noncopyable.h>

namespace pina
{
    class IComponentProvider : public puma::MappedRealizationContainer<Entity, IComponent>, public puma::NonCopyable
    {
    public:
        virtual ~IComponentProvider(){}
    };
}