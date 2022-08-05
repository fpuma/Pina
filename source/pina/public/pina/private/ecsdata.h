#pragma once

#include <utils/containers/mappedrealizationcontainer.h>
#include <pina/entity.h>
#include <pina/component.h>

namespace puma::pina
{
    //Currently we don't exactly need extra internal info for components, but for when we do I am leaving this as reference just in case I forget
    // 
    //class IComponentExtraData
    //{
    //public:
    //    ~IComponentExtraData() {}
    //};

    //template<class T>
    //class ComponentExtraData : public IComponentExtraData
    //{
    //public:

    //    bool enabled = true;
    //    bool entityEnabled = true;
    //};

    enum class EntityStatus
    {
        Enabled,
        Disabled,
        Unassigned,
        Disposed,
    };

    struct EcsData
    {

        std::vector<EntityStatus> entities;
        puma::MappedRealizationContainer<Entity, Component> components;

        //puma::MappedRealizationContainer<Entity, IComponentExtraData> componentsExtraData;
    };
}