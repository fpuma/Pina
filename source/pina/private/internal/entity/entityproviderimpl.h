#pragma once

#include <pina/providers/ecsdata.h>
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

        void disposeEntity( Entity _entity );

        void enableEntity( Entity _entity );

        void disableEntity( Entity _entity );

        bool isEntityEnabled( Entity _entity ) const;

    private:

        EcsData& m_ecsData;

    };
}