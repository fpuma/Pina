#include <internal/component/componentimpl.h>
#include <pina/componentprovider.h>
#include <pina/hidden/pinaevents.h>
#include <pina/hidden/pinaeventmanager.h>
#include <utils/defaultinstance.h>

namespace puma::pina
{
    void ComponentProvider::onAdded( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex )
    {
        _component->m_impl->setEntity( _entity );
        _component->m_impl->setComponentIndex( _componentTypeIndex );
        DefaultInstance<PinaEventManager>::getInstance()->executeEvent( ComponentAddedEvent( _entity, _componentTypeIndex ) );
    }

    void ComponentProvider::onRemoved( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex )
    {
        DefaultInstance<PinaEventManager>::getInstance()->executeEvent( ComponentRemovedEvent( _entity, _componentTypeIndex ) );
    }

    void ComponentProvider::onInterfaceRegistered( std::type_index _interfaceTypeIndex, std::type_index _classTypeIndex )
    {
        DefaultInstance<PinaEventManager>::getInstance()->executeEvent( ComponentInterfaceRegisteredEvent( _interfaceTypeIndex, _classTypeIndex ) );
    }
}