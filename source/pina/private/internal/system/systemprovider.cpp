#include <pina/providers/systemprovider.h>

namespace puma::pina
{

	SystemProvider::SystemProvider( EcsData& _data )
		: m_ecsData( _data )
	{}

	SystemProvider::~SystemProvider() {}

}