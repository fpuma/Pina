#pragma once

#include <memory>
#include <pina/entity.h>
#include <pina/private/ecsdata.h>
#include <utils/noncopyable.h>
#include <utils/numerictypes.h>

namespace puma::pina
{
    struct EcsData;
    class EntityProviderImpl;

    class EntityProvider : public puma::NonCopyable
    {
    public:
        EntityProvider( EcsData& _data );
        virtual ~EntityProvider();
        
        void init( puma::u32 _entityCount );
        void uninit();
        Entity requestEntity();
        void disposeEntity( const Entity& _entity );
        void enableEntity( const Entity& _entity );
        void disableEntity( const Entity& _entity );
        bool isEntityEnabled( const Entity& _entity ) const;

    private:

        std::unique_ptr<EntityProviderImpl> m_impl;
    };


}