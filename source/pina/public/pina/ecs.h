#pragma once

#include <pina/entity.h>
#include <pina/hidden/ecsdata.h>

#include <memory>
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
            std::set<Entity> result;
            InternalEntitesByComponents<Comps...>::get( result, m_data );
            return result;
        }

    private:

        std::unique_ptr<EcsImpl> m_ecsImpl;
        EcsData m_data;
    };

}