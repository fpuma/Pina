#pragma once

#include <pina/component.h>
#include <pina/entity.h>
#include <pina/private/ecsdata.h>
#include <utils/containers/mappedrealizationcontainer.h>
#include <utils/noncopyable.h>


namespace puma::pina
{
    class ComponentProvider : public puma::NonCopyable
    {
    public:
        ComponentProvider( EcsData& _data )
            : m_ecsData( _data )
        {}

        virtual ~ComponentProvider() {}

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
            return m_ecsData.components.add<T>( _entity );
        }

        template<class T>
        void removeComponent( Entity _entity )
        {
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

    private:

        EcsData& m_ecsData;

    };
}