#include <pina/ecs.h>
#include <internal/ecs/ecsimpl.h>
#include <assert.h>

#include <pina/hidden/componentprovider.h>
#include <pina/hidden/entityprovider.h>

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
    
    //REMOVE
    EcsData& ECS::getEcsData()
    {
        return m_ecsImpl->getEcsData();
    }

}