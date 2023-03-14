#pragma once

#include <pina/entity.h>
#include <pina/ecsdata.h>

#include <set>

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

        template<class... Comps>
        std::set<Entity> getEntitesByComponents() const
        {
            return m_data.getEntitesByComponents<Comps...>();
        }

    private:

        EcsData m_data;
    };

}