#include <algorithm>
#include <internal/entity/entityproviderimpl.h>

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

        return result;
    }

    void EntityProviderImpl::disposeEntity( Entity _entity )
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned );
        m_entities[_entity.value()] = EntityStatus::Unassigned;
    }

    void EntityProviderImpl::enableEntity( Entity _entity )
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned );
        //assert( m_ecsData.entityAssignedComponents.contains( _entity ) );
        m_entities[_entity.value()] = EntityStatus::Enabled;

        //m_ecsData.components.visit( _entity, []( std::shared_ptr<Component> component )
        //    {
        //        component->enable();
        //    } );

        //for (const ComponentIndex& compIdx : m_ecsData.entityAssignedComponents.at(_entity))
        //{

        //}

    }

    void EntityProviderImpl::disableEntity( Entity _entity )
    {
        assert( m_entities[_entity.value()] != EntityStatus::Unassigned );
        m_entities[_entity.value()] = EntityStatus::Disabled;

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