#include <internal/entityprovider/entityproviderimpl.h>
#include <pina/private/entityprovider.h>

namespace puma::pina
{
    EntityProvider::EntityProvider( EcsData& _data )
    {
        m_impl = std::make_unique<EntityProviderImpl>( _data );
    }
    EntityProvider::~EntityProvider() {}

    void EntityProvider::init( puma::u32 _entityCount )
    {
        m_impl->init( _entityCount );
    }

    void EntityProvider::uninit()
    {
        m_impl->uninit();
    }

    Entity EntityProvider::requestEntity()
    {
        return m_impl->requestEntity();
    }

    void EntityProvider::disposeEntity( const Entity& _entity )
    {
        m_impl->disposeEntity( _entity );
    }

    void EntityProvider::enableEntity( const Entity& _entity )
    {
        m_impl->enableEntity( _entity );
    }

    void EntityProvider::disableEntity( const Entity& _entity )
    {
        m_impl->disableEntity( _entity );
    }

    bool EntityProvider::isEntityEnabled( const Entity& _entity ) const
    {
        return m_impl->isEntityEnabled( _entity );
    }
}