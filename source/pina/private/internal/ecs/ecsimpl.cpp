#include "ecsimpl.h" 

#include <pina/hidden/componentprovider.h>
#include <pina/hidden/ecsdata.h>
#include <pina/hidden/entityprovider.h>

namespace puma::pina
{

	EcsImpl::EcsImpl()
		: m_entities(std::make_unique<EntityProvider>(m_data))
		, m_components( std::make_unique<ComponentProvider>( m_data ) )
	{}

	EcsImpl::~EcsImpl() {}

	EntityProvider* EcsImpl::getEntityProvider() { return m_entities.get(); }
	ComponentProvider* EcsImpl::getComponentProvider() { return m_components.get(); }

	const EntityProvider* EcsImpl::getEntityProvider() const { return m_entities.get(); }
	const ComponentProvider* EcsImpl::getComponentProvider() const { return m_components.get(); }

	void EcsImpl::uninit()
	{
		m_entities->uninit();
		m_components->uninit();
	}

}