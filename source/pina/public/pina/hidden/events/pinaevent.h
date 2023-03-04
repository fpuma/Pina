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
	};

	class PinaEvent : public IEvent
	{
	public:

		PinaEvent( PinaEventType _type ) : m_type( _type ) {}

		PinaEventType getType() const { return m_type; }

	protected:

		const PinaEventType m_type;

	};
}