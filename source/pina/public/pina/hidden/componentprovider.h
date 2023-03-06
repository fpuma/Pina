#pragma once

#include <pina/component.h>
#include <pina/entity.h>
#include <pina/hidden/ecsdata.h>
#include <pina/hidden/events/pinaeventmanager.h>
#include <pina/hidden/events/pinaevents.h>
#include <utils/containers/mappedrealizationcontainer.h>
#include <utils/defaultinstance.h>
#include <utils/noncopyable.h>

namespace puma::pina
{
    class ComponentProvider final : public MappedRealizationContainer<Entity, Component>, public NonCopyable
    {
    public:
        ComponentProvider() {}

        virtual ~ComponentProvider() {}

        void uninit()
        {
            clear();
        }



    protected:

        void onAdded( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex ) override
        {
            DefaultInstance<PinaEventManager>::getInstance()->executeEvent( ComponentAddedEvent( _entity, _componentTypeIndex ) );
            //if (!m_ecsData.entitiesEnabledComponents.contains( _componentTypeIndex ))
            //{
            //    m_ecsData.entitiesEnabledComponents.insert( { _componentTypeIndex,{} } );
            //}

            //if (!m_ecsData.entityAssignedComponents.contains( _entity ))
            //{
            //    m_ecsData.entityAssignedComponents.insert( { _entity, {} } );
            //}

            //m_ecsData.entityAssignedComponents.at( _entity ).insert( _componentTypeIndex );
            //m_ecsData.entitiesEnabledComponents.at( _componentTypeIndex ).insert( _entity );
        }

        void onRemoved( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex ) override
        {
            //m_ecsData.entitiesEnabledComponents.at( _componentTypeIndex ).erase( _entity );
            //m_ecsData.entityAssignedComponents.at( _entity ).erase( _componentTypeIndex );
        }
    };
}