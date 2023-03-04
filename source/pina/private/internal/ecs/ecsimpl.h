#pragma once

#include <pina/hidden/ecsdata.h>

namespace puma::pina
{
	class EntityProvider;
	class ComponentProvider;

	class EcsImpl
	{
	public:

		EcsImpl();
		~EcsImpl();

		EntityProvider* getEntityProvider();
		ComponentProvider* getComponentProvider();

		const EntityProvider* getEntityProvider() const;
		const ComponentProvider* getComponentProvider() const;

		void uninit();

		//Exposing this to make it compile for now
		EcsData& getEcsData() { return m_data; }

	private:

		std::unique_ptr<EntityProvider> m_entities;// = nullptr;
		std::unique_ptr<ComponentProvider> m_components;// = nullptr;

		EcsData m_data;

	};
}