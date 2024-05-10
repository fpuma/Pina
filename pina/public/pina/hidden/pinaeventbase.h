#pragma once

#include <utils/events/ievent.h>

namespace puma::pina
{
	enum class PinaEventType
	{
		EntityAdded,
		EntityRemoved,
		EntityEnabled,
		EntityDisabled,
		ComponentAdded,
		ComponentRemoved,
		ComponentEnabled,
		ComponentDisabled,
		ComponentInterfaceRegistered,
	};

	class PinaEventBase : public IEvent
	{
	public:

		PinaEventBase( PinaEventType _type ) : m_type( _type ) {}
		virtual ~PinaEventBase() = default;

		PinaEventType getType() const { return m_type; }

	protected:

		const PinaEventType m_type;

	};
}