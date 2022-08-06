#include <algorithm>
#include <internal/entityprovider/entityproviderimpl.h>

namespace puma::pina
{
    EntityProviderImpl::EntityProviderImpl( EcsData& _data )
        : m_ecsData( _data )
    {}
    
    EntityProviderImpl::~EntityProviderImpl()
    {}

    void EntityProviderImpl::init( puma::u32 _entityCount )
    {
        m_ecsData.entities.resize( _entityCount );
    }

    void EntityProviderImpl::uninit()
    {
        assert( std::all_of( m_ecsData.entities.begin(), m_ecsData.entities.end(), []( const EntityStatus& _status )
            {
                return _status == EntityStatus::Unassigned;
            } ) );

        m_ecsData.entities.clear();
    }

    Entity EntityProviderImpl::requestEntity()
    {
        Entity result;

        auto itFoundEntity = std::find( m_ecsData.entities.begin(), m_ecsData.entities.end(), EntityStatus::Unassigned );

        if (m_ecsData.entities.end() != itFoundEntity)
        {
            result = Entity( std::distance( m_ecsData.entities.begin(), itFoundEntity ) );
            *itFoundEntity = EntityStatus::Enabled;
        }
        else
        {
            result = Entity( m_ecsData.entities.size() );
            m_ecsData.entities.push_back( EntityStatus::Enabled );
        }

        return result;
    }

    void EntityProviderImpl::disposeEntity( const Entity& _entity )
    {
        assert( m_ecsData.entities[_entity.value()] != EntityStatus::Unassigned );
        m_ecsData.entities[_entity.value()] = EntityStatus::Unassigned;
    }

    void EntityProviderImpl::enableEntity( const Entity& _entity )
    {
        assert( m_ecsData.entities[_entity.value()] != EntityStatus::Unassigned );
        m_ecsData.entities[_entity.value()] = EntityStatus::Enabled;

        m_ecsData.components.visit( _entity, []( std::shared_ptr<Component> component )
            {
                component->enable();
            } );
    }

    void EntityProviderImpl::disableEntity( const Entity& _entity )
    {
        assert( m_ecsData.entities[_entity.value()] != EntityStatus::Unassigned );
        m_ecsData.entities[_entity.value()] = EntityStatus::Disabled;

        m_ecsData.components.visit( _entity, []( std::shared_ptr<Component> component )
            {
                component->disable();
            } );
    }

    bool EntityProviderImpl::isEntityEnabled( const Entity& _entity ) const
    {
        assert( m_ecsData.entities[_entity.value()] != EntityStatus::Unassigned );
        return m_ecsData.entities[_entity.value()] == EntityStatus::Enabled;
    }
}