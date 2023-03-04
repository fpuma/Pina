#pragma once

#include <memory>

namespace puma::pina
{
    class EcsImpl;
    class EntityProvider;
    class ComponentProvider;

    class ECS
    {
    public:
        ECS();
        virtual ~ECS();

        EntityProvider* getEntityProvider();
        ComponentProvider* getComponentProvider();

        const EntityProvider* getEntityProvider()       const;
        const ComponentProvider* getComponentProvider() const;

    private:

        std::unique_ptr<EcsImpl> m_ecsImpl;
    };

}