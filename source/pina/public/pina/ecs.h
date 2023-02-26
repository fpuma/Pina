#pragma once

#include <memory>

namespace puma::pina
{
    class EcsImpl;
    class EntityProvider;
    class ComponentProvider;
    class SystemProvider;

    //REMOVE
    struct EcsData;

    class ECS
    {
    public:
        ECS();
        virtual ~ECS();

        void initEntities( std::unique_ptr<EntityProvider> _entityProvider = nullptr );
        void initComponents( std::unique_ptr<ComponentProvider> _componentProvider = nullptr );
        void initSystems( std::unique_ptr<SystemProvider> _systemProvider = nullptr );

        EntityProvider* getEntityProvider();
        ComponentProvider* getComponentProvider();
        SystemProvider* getSystemProvider();

        const EntityProvider* getEntityProvider()       const;
        const ComponentProvider* getComponentProvider() const;
        const SystemProvider* getSystemProvider()       const;

        //REMOVE
        EcsData& getEcsData();

    private:

        std::unique_ptr<EcsImpl> m_ecsImpl;
    };

}