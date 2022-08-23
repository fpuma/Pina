#pragma once

#include <pina/private/ecsdata.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace puma::pina
{
    class SystemProvider : public puma::NonCopyable
    {
    public:

        SystemProvider( EcsData& _data )
            : m_ecsData( _data )
        {}

        virtual ~SystemProvider() {}

        template<class T>
        void registerSystem()
        {
            m_ecsData.systems.registerClass<T>();
        }

        template<class Interface, class Realization>
        void registerSystem()
        {
            m_ecsData.systems.registerInterface<Interface, Realization>();
        }

        template<class T>
        std::shared_ptr<T> addSystem()
        {
            return m_ecsData.systems.add<T>();
        }

        template<class T>
        void removeSystem()
        {
            m_ecsData.systems.remove<T>();
        }

        template<class T>
        T* getSystem()
        {
            return m_ecsData.systems.get<T>();
        }

        template<class T>
        const T* getSystem() const
        {
            return m_ecsData.systems.get<T>();
        }

        template<class T>
        std::shared_ptr<T> getSystemSafely()
        {
            return m_ecsData.systems.getSafely<T>();
        }

        template<class T>
        std::shared_ptr<const T> getSystem() const
        {
            return m_ecsData.systems.getSafely<T>();
        }

        template<class T>
        bool containsSystem() const
        {
            return m_ecsData.systems.contains<T>();
        }

    protected:

        void visit( std::function<void( std::shared_ptr<System> sys )> _visitor )
        {
            m_ecsData.systems.visit( _visitor );
        }

        System* getSystem ( std::type_index _idx ) { return m_ecsData.systems.get( _idx ); }
        const System* getSystem ( std::type_index _idx ) const { return m_ecsData.systems.get( _idx ); }
        std::shared_ptr<System> getSystemSafely ( std::type_index _idx ) { return m_ecsData.systems.getSafely( _idx ); }
        std::shared_ptr<const System> getSystemSafely ( std::type_index _idx ) const { return m_ecsData.systems.getSafely( _idx ); }

    private:

        EcsData& m_ecsData;
    };
}