#pragma once

#include "pinaeventbase.h"

#include <pina/entity.h>
#include <typeindex>

namespace puma::pina
{
	class EntityEvent
	{
	public:

		EntityEvent( Entity _entity )
			: m_entity( _entity )
		{}
		virtual ~EntityEvent() = default;

		Entity getEntity()const { return m_entity; }

	private:
		const Entity m_entity;
	};

	class ComponentEvent
	{
	public:

		using ComponentIndex = std::type_index;

		ComponentEvent( Entity _entity, ComponentIndex _compTypeIndex )
			: m_entity( _entity )
			, m_componentTypeIndex( _compTypeIndex )
		{}
		virtual ~ComponentEvent() = default;

		Entity getEntity() const { return m_entity; }
		ComponentIndex getComponentIndex() const { return m_componentTypeIndex; }

	private:
		const Entity m_entity;
		const ComponentIndex m_componentTypeIndex;
	};

	class EntityAddedEvent : public PinaEventBase, public EntityEvent
	{
	public:

		EntityAddedEvent(Entity _entity) 
			: PinaEventBase( PinaEventType::EntityAdded )
			, EntityEvent(_entity) {}
	};

	class EntityRemovedEvent : public PinaEventBase, public EntityEvent
	{
	public:

		EntityRemovedEvent( Entity _entity )
			: PinaEventBase( PinaEventType::EntityRemoved )
			, EntityEvent( _entity ) {}
	};

	class EntityEnabledEvent : public PinaEventBase, public EntityEvent
	{
	public:

		EntityEnabledEvent( Entity _entity )
			: PinaEventBase( PinaEventType::EntityEnabled )
			, EntityEvent( _entity ) {}
	};

	class EntityDisabledEvent : public PinaEventBase, public EntityEvent
	{
	public:

		EntityDisabledEvent( Entity _entity )
			: PinaEventBase( PinaEventType::EntityDisabled )
			, EntityEvent( _entity ) {}
	};

	class ComponentAddedEvent : public PinaEventBase, public ComponentEvent
	{
	public:

		ComponentAddedEvent( Entity _entity, ComponentIndex _componentIndex )
			: PinaEventBase( PinaEventType::ComponentAdded )
			, ComponentEvent(_entity, _componentIndex) {}
	};

	class ComponentRemovedEvent : public PinaEventBase, public ComponentEvent
	{
	public:

		ComponentRemovedEvent( Entity _entity, ComponentIndex _componentIndex )
			: PinaEventBase( PinaEventType::ComponentRemoved )
			, ComponentEvent( _entity, _componentIndex ) {}
	};

	class ComponentEnabledEvent : public PinaEventBase, public ComponentEvent
	{
	public:

		ComponentEnabledEvent( Entity _entity, ComponentIndex _componentIndex )
			: PinaEventBase( PinaEventType::ComponentEnabled )
			, ComponentEvent( _entity, _componentIndex ) {}
	};

	class ComponentDisabledEvent : public PinaEventBase, public ComponentEvent
	{
	public:

		ComponentDisabledEvent( Entity _entity, ComponentIndex _componentIndex )
			: PinaEventBase( PinaEventType::ComponentDisabled )
			, ComponentEvent( _entity, _componentIndex ) {}
	};
}