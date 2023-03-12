#pragma once

#include <pina/entity.h>
#include <utils/noncopyable.h>
#include <utils/numerictypes.h>

#include <memory>

namespace puma::pina
{
    class EntityProviderImpl;

    class EntityProvider final : public NonCopyable
    {
    public:
        EntityProvider();
        virtual ~EntityProvider();
        
        void init( u32 _entityCount );
        void uninit();
        Entity requestEntity();
        void disposeEntity( Entity _entity );
        void enableEntity( Entity _entity );
        void disableEntity( Entity _entity );
        bool isEntityEnabled( Entity _entity ) const;

    private:

        std::unique_ptr<EntityProviderImpl> m_impl;
    };


}