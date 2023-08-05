#pragma once

#include <pina/component.h>
#include <pina/entity.h>
#include <pina/hidden/pinaeventbase.h>
#include <utils/events/ieventlistener.h>

#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <typeindex>

namespace puma::pina
{
	class ComponentProvider;
	class EntityProvider;
	class PinaEventManager;

	class EcsData final : IEventListener<PinaEventBase>
	{
	public:

		EcsData();
		~EcsData();

		EntityProvider* getEntityProvider();
		ComponentProvider* getComponentProvider();

		const EntityProvider* getEntityProvider() const;
		const ComponentProvider* getComponentProvider() const;

		void uninit();

		void onEvent( const PinaEventBase& _event ) override;

		template<class... Comps>
		std::set<Entity> getEntitesByComponents() const
		{
			std::set<Entity> result;
			InternalEntitesByComponents<Comps...>::get( result, m_enabledComponentsMap );
			return result;
		}

	private:

		using ComponentIndex = std::type_index;
		using EnabledComponentsMap = std::unordered_map<ComponentIndex, std::set<Entity>>;
		using AssignedComponentsMap = std::unordered_map<Entity, std::set<ComponentIndex>>;

		template<class... Args>
		struct InternalEntitesByComponents;

		std::unique_ptr<EntityProvider> m_entities;
		std::unique_ptr<ComponentProvider> m_components;
		std::unique_ptr<PinaEventManager> m_eventManager;

		EnabledComponentsMap m_enabledComponentsMap; //This is to keep track the enabled components on entities
		AssignedComponentsMap m_assignedComponentsMap; //This is to keep track of the actual components assigned to entities

		std::unordered_map<std::type_index, std::type_index> m_componentRegistrationMap;

		template<>
		struct InternalEntitesByComponents<>
		{
			static void get( std::set<Entity>& _entities, const EnabledComponentsMap& _enabledComponentsMap ) {}
		};

		template<class First, class... Args>
		struct InternalEntitesByComponents<First, Args...>
		{
			static void get( std::set<Entity>& _entities, const EnabledComponentsMap& _enabledComponentsMap )
			{
				static_assert(std::is_base_of<Component, First>::value); //The given class does not inherit from Component
				auto typeIndex = ComponentIndex( typeid(First) );

				if (_enabledComponentsMap.contains( typeIndex ))
				{
					const std::set<Entity>& compNtts = _enabledComponentsMap.at( typeIndex );

					if (false == compNtts.empty())
					{
						if (_entities.empty())
						{
							_entities.insert( compNtts.begin(), compNtts.end() );
						}
						else
						{
							std::set<Entity> aux = _entities;
							_entities.clear();
							std::set_intersection( aux.begin(), aux.end(), compNtts.begin(), compNtts.end(), std::inserter( _entities, _entities.begin() ) );
						}

						InternalEntitesByComponents<Args...>::get( _entities, _enabledComponentsMap );
					}
					else
					{
						_entities.clear();
					}
				}
				else
				{
					_entities.clear();
				}

			}
		};

	};



}