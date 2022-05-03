#include "systemprovider.h"

#include <algorithm>

namespace puma
{

    void SystemProvider::onAdded( Key _key, ISystem* _system )
    {
        SystemProperties properties = _system->getProperties();

        auto sortCallback = []( const ISystem* _sys1, const ISystem* _sys2 )
        {
            return _sys1->getProperties().priority < _sys2->getProperties().priority;
        };

        if ( properties.updateBitMask & SystemUpdateFlag_Update )
        {
            m_systemsToUpdate.push_back( _system );
            std::sort( m_systemsToUpdate.begin(), m_systemsToUpdate.end(), sortCallback );
        }

        if ( properties.updateBitMask & SystemUpdateFlag_PrePhysicsUpdate )
        {
            m_systemsToUpdatePrePhysics.push_back( _system );
            std::sort( m_systemsToUpdatePrePhysics.begin(), m_systemsToUpdatePrePhysics.end(), sortCallback );
        }

        if ( properties.updateBitMask & SystemUpdateFlag_PostPhysicsUpdate )
        {
            m_systemsToUpdatePostPhysics.push_back( _system );
            std::sort( m_systemsToUpdatePostPhysics.begin(), m_systemsToUpdatePostPhysics.end(), sortCallback );
        }

        if ( properties.updateBitMask & SystemUpdateFlag_QueueRenderables )
        {
            m_systemsToQueueRenderables.push_back( _system );
        }
    }

    void SystemProvider::onRemoved( Key _key, ISystem* _system )
    {
        m_systemsToUpdate.erase( std::remove( m_systemsToUpdate.begin(), m_systemsToUpdate.end(), _system ), m_systemsToUpdate.end() );
        m_systemsToUpdatePrePhysics.erase( std::remove( m_systemsToUpdatePrePhysics.begin(), m_systemsToUpdatePrePhysics.end(), _system ), m_systemsToUpdatePrePhysics.end() );
        m_systemsToUpdatePostPhysics.erase( std::remove( m_systemsToUpdatePostPhysics.begin(), m_systemsToUpdatePostPhysics.end(), _system ), m_systemsToUpdatePostPhysics.end() );
    }

    void SystemProvider::uninit()
    {
        traverse( []( ISystem* _ptr ) 
        {
            _ptr->uninit();
        } );
        m_systemsToUpdate.clear();
        m_systemsToUpdatePrePhysics.clear();
        m_systemsToUpdatePostPhysics.clear();
        clear();
    }
    
    void SystemProvider::update( float _deltaTime )
    {
        for( ISystem* systemPtr : m_systemsToUpdate )
        {
            systemPtr->update( _deltaTime );
        }
    }

    void SystemProvider::prePhysicsUpdate( float _deltaTime )
    {
        for ( ISystem* systemPtr : m_systemsToUpdatePrePhysics )
        {
            systemPtr->prePhysicsUpdate( _deltaTime );
        }
    }

    void SystemProvider::postPhysicsUpdate( float _deltaTime )
    {
        for ( ISystem* systemPtr : m_systemsToUpdatePostPhysics )
        {
            systemPtr->postPhysicsUpdate( _deltaTime );
        }
    }

    void SystemProvider::queueRenderables( IRenderQueue& _renderQueue )
    {
        for ( ISystem* systemPtr : m_systemsToQueueRenderables )
        {
            systemPtr->queueRenderables( _renderQueue );
        }
    }
    
    void SystemProvider::updateSystemsProperties()
    {
        m_systemsToUpdate.clear();
        m_systemsToUpdatePrePhysics.clear();
        m_systemsToUpdatePostPhysics.clear();
        m_systemsToQueueRenderables.clear();

        traverse( [&]( ISystem* _system )
        {
            SystemProperties properties = _system->getProperties();

            if ( properties.updateBitMask & SystemUpdateFlag_Update )
            {
                m_systemsToUpdate.push_back( _system );
            }

            if ( properties.updateBitMask & SystemUpdateFlag_PrePhysicsUpdate )
            {
                m_systemsToUpdatePrePhysics.push_back( _system );
            }

            if ( properties.updateBitMask & SystemUpdateFlag_PostPhysicsUpdate )
            {
                m_systemsToUpdatePostPhysics.push_back( _system );
            }

            if ( properties.updateBitMask & SystemUpdateFlag_QueueRenderables )
            {
                m_systemsToQueueRenderables.push_back( _system );
            }
        } );

        auto sortCallback = []( const ISystem* _sys1, const ISystem* _sys2 )
        {
            return _sys1->getProperties().priority < _sys2->getProperties().priority;
        };

        std::sort( m_systemsToUpdate.begin(), m_systemsToUpdate.end(), sortCallback );
        std::sort( m_systemsToUpdatePrePhysics.begin(), m_systemsToUpdatePrePhysics.end(), sortCallback );
        std::sort( m_systemsToUpdatePostPhysics.begin(), m_systemsToUpdatePostPhysics.end(), sortCallback );
    }
}