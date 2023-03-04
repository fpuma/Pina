#pragma once

#include <pina/component.h>
#include <pina/entity.h>
#include <pina/hidden/ecsdata.h>
#include <utils/containers/mappedrealizationcontainer.h>
#include <utils/noncopyable.h>
#include <iterator>

namespace puma::pina
{
    class ComponentProvider final : public MappedRealizationContainer<Entity, Component>, public NonCopyable
    {
    public:
        ComponentProvider( EcsData& _data )
            : m_ecsData( _data )
        {}

        virtual ~ComponentProvider() {}

        void uninit()
        {
            clear();
        }

        template<class... Comps>
        std::set<Entity> getEntitesByComponents() const
        {
            std::set<Entity> result;
            InternalEntitesByComponents<Comps...>::get( result, m_ecsData );
            return result;
        }

    protected:

        void onAdded( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex ) override
        {
            if (!m_ecsData.entitiesEnabledComponents.contains( _componentTypeIndex ))
            {
                m_ecsData.entitiesEnabledComponents.insert( { _componentTypeIndex,{} } );
            }

            if (!m_ecsData.entityAssignedComponents.contains( _entity ))
            {
                m_ecsData.entityAssignedComponents.insert( { _entity, {} } );
            }

            m_ecsData.entityAssignedComponents.at( _entity ).insert( _componentTypeIndex );
            m_ecsData.entitiesEnabledComponents.at( _componentTypeIndex ).insert( _entity );
        }

        void onRemoved( Entity _entity, std::shared_ptr<Component> _component, std::type_index _componentTypeIndex ) override
        {
            m_ecsData.entitiesEnabledComponents.at( _componentTypeIndex ).erase( _entity );
            m_ecsData.entityAssignedComponents.at( _entity ).erase( _componentTypeIndex );
        }

    private:

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

        EcsData& m_ecsData;

    };
}