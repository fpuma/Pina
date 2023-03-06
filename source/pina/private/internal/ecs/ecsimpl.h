#pragma once

#include <memory>

namespace puma::pina
{
	class EntityProvider;
	class ComponentProvider;
	class PinaEventManager;

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

	private:

		std::unique_ptr<EntityProvider> m_entities;
		std::unique_ptr<ComponentProvider> m_components;
		std::unique_ptr<PinaEventManager> m_eventManager;

	};
}