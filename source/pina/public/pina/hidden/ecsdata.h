#pragma once

#include <pina/component.h>
#include <pina/entity.h>
#include <utils/containers/mappedrealizationcontainer.h>

#include <iterator>
#include <map>
#include <set>

namespace puma::pina
{
    enum class EntityStatus
    {
        Enabled,
        Disabled,
        Unassigned,
        Disposed,
    };

    using ComponentIndex = std::type_index;

    struct EcsData
    {
        std::unordered_map<ComponentIndex, std::set<Entity>> entitiesEnabledComponents; //This is to keep track the enabled components on entities
        std::unordered_map<Entity, std::set<ComponentIndex>> entityAssignedComponents; //This is to keep track of the actual components assigned to entities
    };

    template<class... Args>
    struct InternalEntitesByComponents;

    template<>
    struct InternalEntitesByComponents<>
    {
        static void get( std::set<Entity>& _entities, const EcsData& _ecsData ) {}
    };

    template<class First, class... Args>
    struct InternalEntitesByComponents<First, Args...>
    {
        static void get( std::set<Entity>& _entities, const EcsData& _ecsData )
        {
            static_assert(std::is_base_of<Component, First>::value); //The given class does not inherit from Component
            auto typeIndex = ComponentIndex( typeid(First) );

            if (_ecsData.entitiesEnabledComponents.contains( typeIndex ))
            {
                const std::set<Entity>& compNtts = _ecsData.entitiesEnabledComponents.at( typeIndex );
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
            }

            InternalEntitesByComponents<Args...>::get( _entities, _ecsData );
        }
    };

}