#pragma once

#include <pina/entity.h>
#include <utils/numerictypes.h>

namespace puma::pina
{
    enum class EntityStatus
    {
        Enabled,
        Disabled,
        Unassigned,
        Disposed,
    };

    class EntityProviderImpl
    {
    public:

        EntityProviderImpl() = default;
        ~EntityProviderImpl() = default;

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