#include "componentimpl.h"

#include <pina/hidden/pinaeventmanager.h>
#include <pina/hidden/pinaevents.h>

#include <utils/defaultinstance.h>

namespace puma::pina
{

	ComponentImpl::ComponentImpl()
		: m_enabled( true )
		, m_componentTypeIndex( std::type_index( typeid(void) ) )
	{

	}

	void ComponentImpl::enable() 
	{ 
		m_enabled = true; 
		DefaultInstance<PinaEventManager>::getInstance()->executeEvent( ComponentEnabledEvent( m_entity, m_componentTypeIndex ) );
	}

	void ComponentImpl::disable() 
	{ 
		m_enabled = false; 
		DefaultInstance<PinaEventManager>::getInstance()->executeEvent( ComponentDisabledEvent( m_entity, m_componentTypeIndex ) );
	}
	
	bool ComponentImpl::isEnabled() const 
	{ 
		return m_enabled; 
	}


}