#pragma once

#include <pina/entity.h>
#include <pina/component.h>
#include <utils/containers/mappedrealizationcontainer.h>
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
}