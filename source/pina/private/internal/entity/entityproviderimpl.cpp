#include <internal/entity/entityproviderimpl.h>

#include <pina/hidden/events/pinaeventmanager.h>
#include <pina/hidden/events/pinaevents.h>
#include <utils/defaultinstance.h>

#include <algorithm>
#include <assert.h>

namespace puma::pina
{
    EntityProviderImpl::~EntityProviderImpl()
    {
        assert( std::all_of( m_entities.begin(), m_entities.end(), []( const EntityStatus& _status )
            {
                return _status == EntityStatus::Unassigned;
            } ) ); // Not all entities have been disposed
    }

    void EntityProviderImpl::init( puma::u32 _entityCount )
    {
        m_entities.resize( _entityCount );
    }

    void EntityProviderImpl::uninit()
    {
        int nttIndex = 0;
        for (EntityStatus& nttState : m_entities)
        {
            if (EntityStatus::Unassigned != nttState)
            {
                disposeEntity( Entity( nttIndex ) );
            }
            ++nttIndex;
        }
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
        EntityStatus& entityState = m_entities[_entity.value()];
        assert( entityState != EntityStatus::Unassigned ); //Entity has been already disposed
        if (EntityStatus::Unassigned != entityState)
        {
            entityState = EntityStatus::Unassigned;
            DefaultInstance<PinaEventManager>::getInstance()->executeEvent( EntityRemovedEvent( _entity ) );
        }
    }

    void EntityProviderImpl::enableEntity( Entity _entity )
    {
        EntityStatus& entityState = m_entities[_entity.value()];
        assert( entityState != EntityStatus::Unassigned ); //Entity has been already disposed
        if (EntityStatus::Enabled != entityState)
        {
            entityState = EntityStatus::Enabled;
            DefaultInstance<PinaEventManager>::getInstance()->executeEvent( EntityEnabledEvent( _entity ) );
        }
    }

    void EntityProviderImpl::disableEntity( Entity _entity )
    {
        EntityStatus& entityState = m_entities[_entity.value()];
        assert( entityState != EntityStatus::Unassigned ); //Entity has been already disposed
        if (EntityStatus::Disabled != entityState)
        {
            entityState = EntityStatus::Disabled;
            DefaultInstance<PinaEventManager>::getInstance()->executeEvent( EntityDisabledEvent( _entity ) );
        }
    }

    bool EntityProviderImpl::isEntityEnabled( Entity _entity ) const
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned ); //Entity has been already disposed
        return m_entities[_entity.value()] == EntityStatus::Enabled;
    }
}