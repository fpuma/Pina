#pragma once

#include <pina/private/ecsdata.h>
#include <utils/numerictypes.h>

namespace puma::pina
{
    class EntityProviderImpl
    {
    public:

        EntityProviderImpl( EcsData& _data );
        ~EntityProviderImpl();

        void init( puma::u32 _entityCount );

        void uninit();

        Entity requestEntity();

        void disposeEntity( const Entity& _entity );

        void enableEntity( const Entity& _entity );

        void disableEntity( const Entity& _entity );

        bool isEntityEnabled( const Entity& _entity ) const;

    private:

        EcsData& m_ecsData;

    };
}