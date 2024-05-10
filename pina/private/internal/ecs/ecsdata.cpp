#include <pina/hidden/ecsdata.h>

#include <pina/componentprovider.h>
#include <pina/entityprovider.h>
#include <pina/hidden/pinaeventmanager.h>
#include <pina/hidden/pinaevents.h>
#include <utils/defaultinstance.h>

#include <assert.h>

namespace puma::pina
{
    EcsData::EcsData()
        : m_entities(std::make_unique<EntityProvider>())
        , m_components(std::make_unique<ComponentProvider>())
        , m_eventManager( std::make_unique<PinaEventManager>() )
    {
        DefaultInstance<PinaEventManager>::setInstance( m_eventManager.get() );

        m_eventManager->registerListener<EntityAddedEvent>( this );
        m_eventManager->registerListener<EntityRemovedEvent>( this );
        m_eventManager->registerListener<EntityEnabledEvent>( this );
        m_eventManager->registerListener<EntityDisabledEvent>( this );

        m_eventManager->registerListener<ComponentAddedEvent>( this );
        m_eventManager->registerListener<ComponentRemovedEvent>( this );
        m_eventManager->registerListener<ComponentEnabledEvent>( this );
        m_eventManager->registerListener<ComponentDisabledEvent>( this );

        m_eventManager->registerListener<ComponentInterfaceRegisteredEvent>( this );
    }

    EcsData::~EcsData()
    {
        //uninit();
        DefaultInstance<PinaEventManager>::clear();
    }

    EntityProvider* EcsData::getEntityProvider() { return m_entities.get(); }
    ComponentProvider* EcsData::getComponentProvider() { return m_components.get(); }

    const EntityProvider* EcsData::getEntityProvider() const { return m_entities.get(); }
    const ComponentProvider* EcsData::getComponentProvider() const { return m_components.get(); }

    void EcsData::uninit()
    {
        m_entities->uninit();
    }

    void EcsData::onEvent( const PinaEventBase& _event )
    {
        switch (_event.getType())
        {
        case PinaEventType::EntityAdded:
        {
            const auto& entityAddedEvent = static_cast<const EntityAddedEvent&>(_event);
            assert( !m_assignedComponentsMap.contains( entityAddedEvent.getEntity() ) );
            if (!m_assignedComponentsMap.contains( entityAddedEvent.getEntity() ))
            {
                m_assignedComponentsMap.insert( { entityAddedEvent.getEntity(),{} } );
            }
            break;
        }
        case PinaEventType::EntityRemoved:
        {
            const auto& entityRemovedEvent = static_cast<const EntityRemovedEvent&>(_event);
            Entity removedEntity = entityRemovedEvent.getEntity();
            assert( m_assignedComponentsMap.contains( removedEntity ) ); //This map should contain an element with this entity as a key

            if (m_assignedComponentsMap.contains( removedEntity ))
            {
                auto& componentList = m_assignedComponentsMap.at( removedEntity );
                while (!componentList.empty())
                {
                    m_components->remove( removedEntity, *componentList.begin());
                }
                m_assignedComponentsMap.erase( removedEntity );
            }

            break;
        }
        case PinaEventType::EntityEnabled:
        {
            const auto& entityEnabledEvent = static_cast<const EntityEnabledEvent&>(_event);
            m_components->visit( entityEnabledEvent.getEntity(), [](std::shared_ptr<Component> component)
				{
					component->enable();
				} );
            break;
        }
        case PinaEventType::EntityDisabled:
        {
            const auto& entityDisabledEvent = static_cast<const EntityDisabledEvent&>(_event);
            m_components->visit( entityDisabledEvent.getEntity(), []( std::shared_ptr<Component> component )
                {
                    component->disable();
                } );
            break;
        }
		case PinaEventType::ComponentAdded:
		{
            const auto& compAddedEvent = static_cast<const ComponentAddedEvent&>(_event);
            
            auto compIndex0 = compAddedEvent.getComponentIndex();
            if (!m_enabledComponentsMap.contains( compIndex0 ))
			{
				m_enabledComponentsMap.insert( { compIndex0,{} } );
			}
            
            m_enabledComponentsMap.at( compIndex0 ).insert( compAddedEvent.getEntity() );
            m_assignedComponentsMap.at( compAddedEvent.getEntity() ).insert( compIndex0 );
            
            if (m_componentRegistrationMap.contains( compIndex0 ))
            {
                auto compIndex1 = m_componentRegistrationMap.at( compIndex0 );
                if (!m_enabledComponentsMap.contains( compIndex1 ))
                {
                    m_enabledComponentsMap.insert( { compIndex1,{} } );
                }
                m_enabledComponentsMap.at( compIndex1 ).insert( compAddedEvent.getEntity() );
                m_assignedComponentsMap.at( compAddedEvent.getEntity() ).insert( compIndex1 );
            }
            
			break;
		}
        case PinaEventType::ComponentRemoved:
        {
            const auto& compRemovedEvent = static_cast<const ComponentRemovedEvent&>(_event);
            
            auto compIndex0 = compRemovedEvent.getComponentIndex();
            m_enabledComponentsMap.at( compIndex0 ).erase( compRemovedEvent.getEntity() );
            m_assignedComponentsMap.at( compRemovedEvent.getEntity() ).erase( compIndex0 );

            if (m_componentRegistrationMap.contains( compIndex0 ))
            {
                auto compIndex1 = m_componentRegistrationMap.at( compIndex0 );
                m_enabledComponentsMap.at( compIndex1 ).erase( compRemovedEvent.getEntity() );
                m_assignedComponentsMap.at( compRemovedEvent.getEntity() ).erase( compIndex1 );
            }

            break;
        }
        case PinaEventType::ComponentEnabled:
        {
            const auto& compEnabledEvent = static_cast<const ComponentEnabledEvent&>(_event);

            auto compIndex0 = compEnabledEvent.getComponentIndex();
            m_enabledComponentsMap.at( compIndex0 ).insert( compEnabledEvent.getEntity() );
            
            if (m_componentRegistrationMap.contains( compIndex0 ))
            {
                auto compIndex1 = m_componentRegistrationMap.at( compIndex0 );
                m_enabledComponentsMap.at( compIndex1 ).insert( compEnabledEvent.getEntity() );
            }

            break;
        }
        case PinaEventType::ComponentDisabled:
        {
            const auto& compDisabledEvent = static_cast<const ComponentDisabledEvent&>(_event);

            auto compIndex0 = compDisabledEvent.getComponentIndex();
            m_enabledComponentsMap.at( compIndex0 ).erase( compDisabledEvent.getEntity() );
            
            if (m_componentRegistrationMap.contains( compIndex0 ))
            {
                auto compIndex1 = m_componentRegistrationMap.at( compIndex0 );
                m_enabledComponentsMap.at( compIndex1 ).erase( compDisabledEvent.getEntity() );
            }

            break;
        }
        case PinaEventType::ComponentInterfaceRegistered:
        {
            const auto& compInterfaceRegEvent = static_cast<const ComponentInterfaceRegisteredEvent&>(_event);

            m_componentRegistrationMap.insert( { compInterfaceRegEvent.getComponentInterfaceIndex(), compInterfaceRegEvent.getComponentClassIndex() } );
            m_componentRegistrationMap.insert( { compInterfaceRegEvent.getComponentClassIndex(), compInterfaceRegEvent.getComponentInterfaceIndex() } );

            break;
        }
        default:
            break;
        }
    }

}