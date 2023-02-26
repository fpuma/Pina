#include "ecsimpl.h" 

#include <pina/providers/componentprovider.h>
#include <pina/providers/ecsdata.h>
#include <pina/providers/entityprovider.h>
#include <pina/providers/systemprovider.h>

namespace puma::pina
{

	EcsImpl::EcsImpl()
		: m_entities(nullptr)
		, m_components(nullptr)
		, m_systems(nullptr)
	{}

	EcsImpl::~EcsImpl() {}

	void EcsImpl::setEntityProvider( std::unique_ptr<EntityProvider> _entityProvider ) { m_entities = std::move( _entityProvider ); }
	void EcsImpl::setComponentProvider( std::unique_ptr<ComponentProvider> _componentProvider ) { m_components = std::move( _componentProvider ); }
	void EcsImpl::setSystemProvider( std::unique_ptr<SystemProvider> _systemProvider ) { m_systems = std::move( _systemProvider ); }

	EntityProvider* EcsImpl::getEntityProvider() { return m_entities.get(); }
	ComponentProvider* EcsImpl::getComponentProvider() { return m_components.get(); }
	SystemProvider* EcsImpl::getSystemProvider() { return m_systems.get(); }

	const EntityProvider* EcsImpl::getEntityProvider() const { return m_entities.get(); }
	const ComponentProvider* EcsImpl::getComponentProvider() const { return m_components.get(); }
	const SystemProvider* EcsImpl::getSystemProvider() const { return m_systems.get(); }

	void EcsImpl::uninit()
	{
		m_entities->uninit();
		m_components->uninit();
		m_systems->uninit();
	}

}