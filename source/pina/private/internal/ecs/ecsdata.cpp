#include <pina/hidden/ecsdata.h>

#include <pina/hidden/componentprovider.h>
#include <pina/hidden/entityprovider.h>
#include <pina/hidden/events/pinaeventmanager.h>
#include <pina/hidden/events/pinaevents.h>
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
        m_components->uninit();
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
                for (const ComponentIndex& componentIndex : componentList)
                {
                    m_components->remove( removedEntity, componentIndex );
                }
                m_assignedComponentsMap.erase( removedEntity );
            }

            //for (auto& componentEntitiesMap : m_enabledComponentsMap)
            //{
            //    auto& entitiesList = componentEntitiesMap.second;
            //    assert( !entitiesList.contains( removedEntity ) ); //Not all components have been removed from this entity
            //    entitiesList.erase( removedEntity );
            //}

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
			if (!m_enabledComponentsMap.contains( compAddedEvent.getComponentIndex() ))
			{
				m_enabledComponentsMap.insert( { compAddedEvent.getComponentIndex(),{} } );
			}

            m_enabledComponentsMap.at( compAddedEvent.getComponentIndex() ).insert( compAddedEvent.getEntity() );
            m_assignedComponentsMap.at( compAddedEvent.getEntity() ).insert( compAddedEvent.getComponentIndex() );
			break;
		}
        case PinaEventType::ComponentRemoved:
        {
            const auto& compRemovedEvent = static_cast<const ComponentRemovedEvent&>(_event);
            m_enabledComponentsMap.at( compRemovedEvent.getComponentIndex() ).erase( compRemovedEvent.getEntity() );
            m_assignedComponentsMap.at( compRemovedEvent.getEntity() ).erase( compRemovedEvent.getComponentIndex() );
            break;
        }
        case PinaEventType::ComponentEnabled:
        {
            const auto& compEnabledEvent = static_cast<const ComponentEnabledEvent&>(_event);
            m_enabledComponentsMap.at( compEnabledEvent.getComponentIndex() ).insert( compEnabledEvent.getEntity() );
            break;
        }
        case PinaEventType::ComponentDisabled:
        {
            const auto& compDisabledEvent = static_cast<const ComponentDisabledEvent&>(_event);
            m_enabledComponentsMap.at( compDisabledEvent.getComponentIndex() ).erase( compDisabledEvent.getEntity() );
            break;
        }
        default:
            break;
        }
    }

}