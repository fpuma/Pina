#pragma once

#include <pina/private/componentprovider.h>
#include <pina/private/ecsdata.h>
#include <pina/private/entityprovider.h>
#include <pina/private/systemprovider.h>
#include <memory>
#include <type_traits>

namespace puma::pina
{
    class ECS
    {
    public:
        ECS() {}
        virtual ~ECS()
        {
            uninit();
        }

        template<class T = EntityProvider>
        void initEntities() { init<EntityProvider, T>( m_entities ); }

        template<class T = ComponentProvider>
        void initComponents() { init<ComponentProvider, T>( m_components ); }

        template<class T = SystemProvider>
        void initSystems() { init<SystemProvider, T>( m_systems ); }

        EntityProvider* getEntityProvider()         { assert( nullptr != m_entities );    return m_entities.get(); }
        ComponentProvider* getComponentProvider()   { assert( nullptr != m_components ); return m_components.get(); }
        SystemProvider* getSystemProvider()         { assert( nullptr != m_systems );    return m_systems.get(); }

        const EntityProvider* getEntityProvider()       const   { assert( nullptr != m_entities );    return m_entities.get(); }
        const ComponentProvider* getComponentProvider() const   { assert( nullptr != m_components ); return m_components.get(); }
        const SystemProvider* getSystemProvider()       const   { assert( nullptr != m_systems );    return m_systems.get(); }

    private:

        template<class Base, class T>
        void init( std::unique_ptr<Base>& _member )
        {
            static_assert(std::is_base_of<Base, T>::value);
            assert( nullptr == _member ); // The member has already been initialized
            _member = std::make_unique<T>( m_data );
        }

        void uninit()
        {
            m_entities->uninit();
            m_components->uninit();
            m_systems->uninit();
        }

        std::unique_ptr<EntityProvider> m_entities = nullptr;
        std::unique_ptr<ComponentProvider> m_components = nullptr;
        std::unique_ptr<SystemProvider> m_systems = nullptr;

        EcsData m_data;
    };

}