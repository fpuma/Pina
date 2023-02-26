#include <pina/entity.h>
#include <pina/system.h>
#include <utils/numerictypes.h>
#include "testcomponents.h"
#include <vector>

#include <pina/providers/componentprovider.h>
#include <pina/providers/systemprovider.h>
#include <pina/providers/entityprovider.h>

#include <pina/ecs.h>

class TestSystemBase :public puma::pina::System
{
public:

    virtual void update( puma::pina::EntityProvider& _entityProvider, puma::pina::ComponentProvider& _componentProvider ) = 0;
};

class SystemA : public TestSystemBase
{
public:

    void update( puma::pina::EntityProvider& _entityProvider, puma::pina::ComponentProvider& _componentProvider ) override
    {
        for (puma::pina::Entity ntt : m_entities)
        {
            ComponentA* comp = _componentProvider.getComponent<ComponentA>( ntt );
            comp->setNumber( comp->getNumber() + 1 );
        }
    }

    void uninit()
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

class SystemB : public TestSystemBase
{
public:

    void update( puma::pina::EntityProvider& _entityProvider, puma::pina::ComponentProvider& _componentProvider ) override
    {
        for (puma::pina::Entity ntt : m_entities)
        {
            ComponentB* comp = _componentProvider.getComponent<ComponentB>( ntt );
            comp->setNumber( comp->getNumber() + 1 );
        }
    }

    void uninit()
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

class TestSystemProvider : public puma::pina::SystemProvider
{
public:

    TestSystemProvider( puma::pina::EcsData& _data )
        : puma::pina::SystemProvider( _data )
    {}

    void update( puma::pina::EntityProvider& _entityProvider, puma::pina::ComponentProvider& _componentProvider )
    {
        visit( [&]( std::shared_ptr<puma::pina::System> _system )
            {
                static_cast<TestSystemBase*>(_system.get())->update( _entityProvider, _componentProvider );
            } );
    }
};