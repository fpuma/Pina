#include <pina/ecs.h>
#include <internal/ecs/ecsimpl.h>
#include <assert.h>

#include <pina/providers/systemprovider.h>
#include <pina/providers/componentprovider.h>
#include <pina/providers/entityprovider.h>

namespace puma::pina
{
    ECS::ECS()
    {
        m_ecsImpl = std::make_unique<EcsImpl>();
    }

    ECS::~ECS()
    {
        m_ecsImpl->uninit();
    }

    void ECS::initEntities( std::unique_ptr<EntityProvider> _entityProvider )
    {
        if (nullptr != _entityProvider)
        {
            m_ecsImpl->setEntityProvider( std::move( _entityProvider ) );
        }
        else
        {
            m_ecsImpl->setEntityProvider( std::make_unique<EntityProvider>( m_ecsImpl->getEcsData() ) );
        }
    }

    void ECS::initComponents( std::unique_ptr<ComponentProvider> _componentProvider )
    {
        if (nullptr != _componentProvider)
        {
            m_ecsImpl->setComponentProvider( std::move( _componentProvider ) );
        }
        else
        {
            m_ecsImpl->setComponentProvider( std::make_unique<ComponentProvider>( m_ecsImpl->getEcsData() ) );
        }
    }

    void ECS::initSystems( std::unique_ptr<SystemProvider> _systemProvider )
    {
        if(nullptr != _systemProvider)
        {
            m_ecsImpl->setSystemProvider( std::move( _systemProvider ) );
        }
        else
        {
            m_ecsImpl->setSystemProvider(  std::make_unique<SystemProvider>( m_ecsImpl->getEcsData() ) );
        }
    }

    EntityProvider* ECS::getEntityProvider() 
    { 
        assert( nullptr != m_ecsImpl->getEntityProvider());
        return m_ecsImpl->getEntityProvider();
    }

    ComponentProvider* ECS::getComponentProvider() 
    { 
        assert( nullptr != m_ecsImpl->getComponentProvider() ); 
        return m_ecsImpl->getComponentProvider();
    }

    SystemProvider* ECS::getSystemProvider() 
    { 
        assert( nullptr != m_ecsImpl->getSystemProvider() );    
        return m_ecsImpl->getSystemProvider();
    }

    const EntityProvider* ECS::getEntityProvider()       const 
    { 
        assert( nullptr != m_ecsImpl->getEntityProvider() );
        return m_ecsImpl->getEntityProvider();
    }
    
    const ComponentProvider* ECS::getComponentProvider() const 
    { 
        assert( nullptr != m_ecsImpl->getComponentProvider() );
        return m_ecsImpl->getComponentProvider();
    }
    
    const SystemProvider* ECS::getSystemProvider()       const 
    { 
        assert( nullptr != m_ecsImpl->getSystemProvider() );
        return m_ecsImpl->getSystemProvider();
    }

    //REMOVE
    EcsData& ECS::getEcsData()
    {
        return m_ecsImpl->getEcsData();
    }

}