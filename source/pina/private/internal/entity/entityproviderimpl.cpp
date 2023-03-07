#include <internal/entity/entityproviderimpl.h>

#include <pina/hidden/events/pinaeventmanager.h>
#include <pina/hidden/events/pinaevents.h>
#include <utils/defaultinstance.h>

#include <algorithm>
#include <assert.h>

namespace puma::pina
{
    void EntityProviderImpl::init( puma::u32 _entityCount )
    {
        m_entities.resize( _entityCount );
    }

    void EntityProviderImpl::uninit()
    {
        assert( std::all_of( m_entities.begin(), m_entities.end(), []( const EntityStatus& _status )
            {
                return _status == EntityStatus::Unassigned;
            } ) );

        m_entities.clear();
    }

    Entity EntityProviderImpl::requestEntity()
    {
        Entity result;

        auto itFoundEntity = std::find( m_entities.begin(), m_entities.end(), EntityStatus::Unassigned );

        if (m_entities.end() != itFoundEntity)
        {
            result = Entity( std::distance( m_entities.begin(), itFoundEntity ) );
            *itFoundEntity = EntityStatus::Enabled;
        }
        else
        {
            result = Entity( m_entities.size() );
            m_entities.push_back( EntityStatus::Enabled );
        }
        DefaultInstance<PinaEventManager>::getInstance()->executeEvent( EntityAddedEvent( result ) );
        return result;
    }

    void EntityProviderImpl::disposeEntity( Entity _entity )
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned );
        m_entities[_entity.value()] = EntityStatus::Unassigned;
        DefaultInstance<PinaEventManager>::getInstance()->executeEvent( EntityRemovedEvent( _entity ) );
    }

    void EntityProviderImpl::enableEntity( Entity _entity )
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned );
        m_entities[_entity.value()] = EntityStatus::Enabled;
        DefaultInstance<PinaEventManager>::getInstance()->executeEvent( EntityEnabledEvent( _entity ) );




        //for (const ComponentIndex& compIdx : m_ecsData.entityAssignedComponents.at(_entity))
        //{

        //}

    }

    void EntityProviderImpl::disableEntity( Entity _entity )
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned );
        m_entities[_entity.value()] = EntityStatus::Disabled;
        DefaultInstance<PinaEventManager>::getInstance()->executeEvent( EntityDisabledEvent( _entity ) );

        //if (m_ecsData.components.contains( _entity ))
        //{
        //    m_ecsData.components.visit( _entity, []( std::shared_ptr<Component> component )
        //        {
        //            component->disable();
        //        } );
        //}

    }

    bool EntityProviderImpl::isEntityEnabled( Entity _entity ) const
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned );
        return m_entities[_entity.value()] == EntityStatus::Enabled;
    }
}