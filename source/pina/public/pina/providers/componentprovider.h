#pragma once

#include <pina/component.h>
#include <pina/entity.h>
#include <pina/providers/ecsdata.h>
#include <utils/containers/mappedrealizationcontainer.h>
#include <utils/noncopyable.h>
#include <iterator>

namespace puma::pina
{
    class ComponentProvider : public puma::NonCopyable
    {
    public:
        ComponentProvider( EcsData& _data )
            : m_ecsData( _data )
        {}

        virtual ~ComponentProvider() {}

        void uninit()
        {
            assert( m_ecsData.components.size() == 0 ); // Not all components have been removed
            m_ecsData.components.clear();
        }

        template<class T>
        void registerComponent()
        {
            m_ecsData.components.registerClass<T>();
        }

        template<class Interface, class Realization>
        void registerComponent()
        {
            m_ecsData.components.registerInterface<Interface, Realization>();
        }

        template<class T>
        std::shared_ptr<T> addComponent( Entity _entity )
        {
            auto typeIndex = ComponentIndex( typeid( T ) );
            if ( !m_ecsData.entitiesEnabledComponents.contains(typeIndex))
            {
                m_ecsData.entitiesEnabledComponents.insert( { typeIndex,{} } );
            }

            if (!m_ecsData.entityAssignedComponents.contains( _entity ))
            {
                m_ecsData.entityAssignedComponents.insert( { _entity, {} } );
            }

            m_ecsData.entityAssignedComponents.at( _entity ).insert( typeIndex );
            m_ecsData.entitiesEnabledComponents.at( typeIndex ).insert( _entity );
            return m_ecsData.components.add<T>( _entity );
        }

        template<class T>
        void removeComponent( Entity _entity )
        {
            auto typeIndex = ComponentIndex( typeid(T) );

            m_ecsData.entitiesEnabledComponents.at( typeIndex ).erase( _entity );
            m_ecsData.entityAssignedComponents.at( _entity ).erase( typeIndex );
            m_ecsData.components.remove<T>( _entity );
        }

        template<class T>
        T* getComponent( Entity _entity )
        {
            return m_ecsData.components.get<T>( _entity );
        }

        template<class T>
        const T* getComponent( Entity _entity ) const
        {
            return m_ecsData.components.get<T>( _entity );
        }

        template<class T>
        std::shared_ptr<T> getComponentSafely( Entity _entity )
        {
            return m_ecsData.components.getSafely<T>( _entity );
        }

        template<class T>
        std::shared_ptr<const T> getComponent( Entity _entity ) const
        {
            return m_ecsData.components.getSafely<T>( _entity );
        }

        template<class T>
        bool containsComponent( Entity _entity ) const
        {
            return m_ecsData.components.contains<T>( _entity );
        }

        template<class... Comps>
        std::set<Entity> getEntitesByComponents() const
        {
            std::set<Entity> result;
            InternalEntitesByComponents<Comps...>::get( result, m_ecsData );
            return result;
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