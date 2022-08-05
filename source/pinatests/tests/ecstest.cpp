#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <pina/ecs.h>
#include "testcomponents.h"

using namespace puma;
using namespace puma::pina;

TEST( ECS, Tests )
{
    ECS ecs;

    EntityProvider& nttProvider = ecs.getEntityProvider();
    ComponentProvider& componentProvider = ecs.getComponentProvider();

    componentProvider.registerComponent<ComponentA>();
    componentProvider.registerComponent<ComponentB>();

    Entity entity1 = nttProvider.requestEntity();

#ifdef _DEBUG
    EXPECT_DEATH( componentProvider.getComponent<ComponentA>( entity1 ), "itElement != m_elements.end" );
#else
    EXPECT_EQ( nullptr, componentProvider.getComponent<ComponentA>( entity1 ) );
#endif

    EXPECT_FALSE( componentProvider.containsComponent<ComponentA>( entity1 ) );

    auto ca1 = componentProvider.addComponent<ComponentA>( entity1 );

    EXPECT_NE( nullptr, ca1 );

}