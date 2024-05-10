#pragma once

#include <pina/component.h>
#include <pina/entity.h>
#include <utils/containers/mappedrealizationcontainer.h>
#include <utils/noncopyable.h>

namespace puma::pina
{
    class ComponentProvider final : public MappedRealizationContainer<Entity, Component>, public NonCopyable
    {
    public:
        ComponentProvider() {}

        virtual ~ComponentProvider() {}

    protected:

        void onAdded( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex ) override;
        void onRemoved( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex ) override;
        void onInterfaceRegistered( std::type_index _interfaceTypeIndex, std::type_index _classTypeIndex ) override;
    };
}