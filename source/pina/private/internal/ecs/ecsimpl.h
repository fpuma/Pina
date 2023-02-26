#pragma once

#include <pina/providers/ecsdata.h>

namespace puma::pina
{
	class EntityProvider;
	class ComponentProvider;
	class SystemProvider;

	class EcsImpl
	{
	public:

		EcsImpl();
		~EcsImpl();

		void setEntityProvider( std::unique_ptr<EntityProvider> _entityProvider );
		void setComponentProvider( std::unique_ptr<ComponentProvider> _componentProvider );
		void setSystemProvider( std::unique_ptr<SystemProvider> _systemProvider );

		EntityProvider* getEntityProvider();
		ComponentProvider* getComponentProvider();
		SystemProvider* getSystemProvider();

		const EntityProvider* getEntityProvider() const;
		const ComponentProvider* getComponentProvider() const;
		const SystemProvider* getSystemProvider() const;

		void uninit();

		//Exposing this to make it compile for now
		EcsData& getEcsData() { return m_data; }

	private:

		std::unique_ptr<EntityProvider> m_entities;// = nullptr;
		std::unique_ptr<ComponentProvider> m_components;// = nullptr;
		std::unique_ptr<SystemProvider> m_systems;// = nullptr;

		EcsData m_data;

	};
}