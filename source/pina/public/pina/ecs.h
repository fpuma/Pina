#pragma once

#include <pina/private/componentprovider.h>
#include <pina/private/ecsdata.h>
#include <pina/private/entityprovider.h>
#include <pina/private/systemprovider.h>

namespace puma::pina
{
    class ECS
    {
    public:
        ECS()
            : m_components( m_data )
            , m_entities( m_data )
            , m_systems( m_data )
        {}
        ~ECS() {}

        EntityProvider& getEntityProvider() { return m_entities; }
        ComponentProvider& getComponentProvider() { return m_components; }
        SystemProvider& getSystemProvider() { return m_systems; }

        const EntityProvider& getEntityProvider() const { return m_entities; }
        const ComponentProvider& getComponentProvider() const { return m_components; }
        const SystemProvider& getSystemProvider() const { return m_systems; }

    private:

        EntityProvider m_entities;
        ComponentProvider m_components;
        SystemProvider m_systems;

        EcsData m_data;
    };

}