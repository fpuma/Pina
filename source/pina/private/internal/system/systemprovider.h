#pragma once

#include <pina/system/isystemprovider.h>

namespace puma
{

    class IRenderQueue;
    class ISystem;

    class SystemProvider final : public ISystemProvider
    {
    public:

        void uninit();
        void prePhysicsUpdate( float _deltaTime );
        void update( float _deltaTime );
        void postPhysicsUpdate( float _deltaTime );

        void queueRenderables( IRenderQueue& _renderQueue );

        void updateSystemsProperties() override;

    protected:

        void onAdded( Key _key, ISystem* _system ) override;
        void onRemoved( Key _key, ISystem* _system ) override;

    private:

        std::vector<ISystem*> m_systemsToUpdate;
        std::vector<ISystem*> m_systemsToUpdatePrePhysics;
        std::vector<ISystem*> m_systemsToUpdatePostPhysics;
        std::vector<ISystem*> m_systemsToQueueRenderables;
    };
}