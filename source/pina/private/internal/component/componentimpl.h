#pragma once

#include <pina/entity.h>

#include <typeindex>

namespace puma::pina
{
    class ComponentImpl 
    {
    public:
        
        ComponentImpl();

        void enable();
        void disable();
        bool isEnabled() const;

        void setEntity( Entity _entity ) { m_entity = _entity; }
        Entity getEntity() const { return m_entity; }

        void setComponentIndex( std::type_index _index ) { m_componentTypeIndex = _index; }
        std::type_index getComponentIndex() const { return m_componentTypeIndex; }

    private:

        bool m_enabled;
        Entity m_entity;
        std::type_index m_componentTypeIndex;
    };

}