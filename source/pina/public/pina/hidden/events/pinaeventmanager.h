#pragma once

#include <utils/events/eventmanager.h>
#include <pina/hidden/events/pinaeventbase.h>

namespace puma::pina
{
	class PinaEventManager final : public EventManager<PinaEventBase>
	{};
}