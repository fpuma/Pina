#include <internal/component/componentimpl.h>
#include <pina/hidden/componentprovider.h>
#include <pina/hidden/events/pinaevents.h>
#include <pina/hidden/events/pinaeventmanager.h>
#include <utils/defaultinstance.h>

namespace puma::pina
{
    void ComponentProvider::uninit()
    {
        clear();
    }

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
}