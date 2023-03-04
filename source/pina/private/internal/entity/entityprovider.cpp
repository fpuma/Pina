#include <pina/hidden/entityprovider.h>
#include <internal/entity/entityproviderimpl.h>

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

    void EntityProvider::disposeEntity( Entity _entity )
    {
        m_impl->disposeEntity( _entity );
    }

    void EntityProvider::enableEntity( Entity _entity )
    {
        m_impl->enableEntity( _entity );
    }

    void EntityProvider::disableEntity( Entity _entity )
    {
        m_impl->disableEntity( _entity );
    }

    bool EntityProvider::isEntityEnabled( Entity _entity ) const
    {
        return m_impl->isEntityEnabled( _entity );
    }
}