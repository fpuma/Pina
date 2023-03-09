#pragma once

#include <pina/entity.h>
#include <utils/numerictypes.h>

namespace puma::pina
{
    enum class EntityStatus
    {
        Unassigned,
        Enabled,
        Disabled,
        //Disposed, //I plan to use this state in case we want to debug if a disposed entity is being reused
    };

    class EntityProviderImpl final
    {
    public:

        EntityProviderImpl() = default;
        ~EntityProviderImpl();

        void init( puma::u32 _entityCount );

        void uninit();

        Entity requestEntity();

        void disposeEntity( Entity _entity );

        void enableEntity( Entity _entity );

        void disableEntity( Entity _entity );

        bool isEntityEnabled( Entity _entity ) const;

    private:

        std::vector<EntityStatus> m_entities;
    };
}