#include <pina/ecs.h>

namespace puma::pina
{
	ECS::ECS()
	{}

	ECS::~ECS()
	{}


	EntityProvider* ECS::getEntityProvider() { return m_data.getEntityProvider(); }
	ComponentProvider* ECS::getComponentProvider() { return m_data.getComponentProvider(); }

	const EntityProvider* ECS::getEntityProvider()       const { return m_data.getEntityProvider(); }
	const ComponentProvider* ECS::getComponentProvider() const { return m_data.getComponentProvider(); }
}