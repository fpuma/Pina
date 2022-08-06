#include <pina/entity.h>
#include <pina/system.h>
#include <utils/numerictypes.h>
#include "testcomponents.h"
#include <vector>

#include <pina/ecs.h>

class SystemA : public puma::pina::System
{
public:

    void update( puma::pina::EntityProvider& _entityProvider, puma::pina::ComponentProvider& _componentProvider, float _deltaTime ) override
    {
        for (puma::pina::Entity ntt : m_entities)
        {
            ComponentA* comp = _componentProvider.getComponent<ComponentA>( ntt );
            comp->setNumber( comp->getNumber() + 1 );
        }
    }

    void uninit() override
    {
        m_entities.clear();
    }

    void registerEntity( puma::pina::Entity _entity )
    {
        m_entities.push_back( _entity );
    }

private:

    std::vector<puma::pina::Entity> m_entities;

};

class SystemB : public puma::pina::System
{
public:

    void update( puma::pina::EntityProvider& _entityProvider, puma::pina::ComponentProvider& _componentProvider, float _deltaTime ) override
    {
        for (puma::pina::Entity ntt : m_entities)
        {
            ComponentB* comp = _componentProvider.getComponent<ComponentB>( ntt );
            comp->setNumber( comp->getNumber() + 1 );
        }
    }

    void uninit() override
    {
        m_entities.clear();
    }

    void registerEntity( puma::pina::Entity _entity )
    {
        m_entities.push_back( _entity );
    }

private:

    std::vector<puma::pina::Entity> m_entities;
};