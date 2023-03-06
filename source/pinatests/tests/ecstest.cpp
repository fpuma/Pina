#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <pina/ecs.h>

#include <pina/hidden/componentprovider.h>
#include <pina/hidden/entityprovider.h>

#include "testcomponents.h"

TEST( ECS, Tests )
{
    puma::pina::ECS ecs;

    puma::pina::EntityProvider* nttProvider = ecs.getEntityProvider();
    puma::pina::ComponentProvider* componentProvider = ecs.getComponentProvider();
    
    componentProvider->registerClass<ComponentA>();
    componentProvider->registerClass<ComponentB>();

    puma::pina::Entity entity0 = nttProvider->requestEntity();

#ifdef _DEBUG
    EXPECT_DEATH( componentProvider->get<ComponentA>( entity0 ), "itElement != m_elements.end" );
#else
    EXPECT_EQ( nullptr, componentProvider->get<ComponentA>( entity0 ) );
#endif

    EXPECT_FALSE( componentProvider->contains<ComponentA>( entity0 ) );

    std::shared_ptr<ComponentA> ca0 = componentProvider->add<ComponentA>( entity0 );

    EXPECT_NE( nullptr, ca0 );

    puma::pina::Entity entity1 = nttProvider->requestEntity();
    puma::pina::Entity entity2 = nttProvider->requestEntity();
    puma::pina::Entity entity3 = nttProvider->requestEntity();

    auto ca1 = componentProvider->add<ComponentA>( entity1 );

    auto ca2 = componentProvider->add<ComponentA>( entity2 );
    auto cb2 = componentProvider->add<ComponentB>( entity2 );

    auto cb3 = componentProvider->add<ComponentB>( entity3 );

    //EXPECT_EQ( 1, ca0->getNumber() );

    //EXPECT_EQ( 2, ca0->getNumber() );
    //EXPECT_EQ( 1, ca1->getNumber() );
    //EXPECT_EQ( 1, ca2->getNumber() );

    //EXPECT_EQ( 2, ca0->getNumber() );
    //EXPECT_EQ( 1, ca1->getNumber() );
    //EXPECT_EQ( 1, ca2->getNumber() );
    //EXPECT_EQ( 1, cb2->getNumber() );
    //EXPECT_EQ( 1, cb3->getNumber() );

    nttProvider->disableEntity( entity2 );
    //EXPECT_FALSE( ca2->isEnabled() );
    //EXPECT_FALSE( cb2->isEnabled() );

    nttProvider->enableEntity( entity2 );

    EXPECT_TRUE( ca2->isEnabled() );
    EXPECT_TRUE( cb2->isEnabled() );

    //EXPECT_EQ( 2, ca2->getNumber() );
    //EXPECT_EQ( 2, cb2->getNumber() );


    //ENTITIES BY COMPONENTS
    auto ntts = ecs.getEntitesByComponents<ComponentA, ComponentB>();
    //EXPECT_EQ( ntts.size(), 1 );
    //EXPECT_EQ( *ntts.begin(), entity2);

    componentProvider->add<ComponentA>( entity3 );
    ntts = ecs.getEntitesByComponents<ComponentA, ComponentB>();

    //EXPECT_EQ( ntts.size(), 2 );
    auto nttsBegin = ntts.begin();
    //EXPECT_EQ( *nttsBegin, entity2 );
    //std::advance( nttsBegin, 1 );
    //EXPECT_EQ( *nttsBegin, entity3 );


    //UNINIT
    componentProvider->remove<ComponentA>( entity0 );
    componentProvider->remove<ComponentA>( entity1 );
    componentProvider->remove<ComponentA>( entity2 );
    componentProvider->remove<ComponentB>( entity2 );
    componentProvider->remove<ComponentA>( entity3 );
    componentProvider->remove<ComponentB>( entity3 );

    nttProvider->disposeEntity( entity0 );
    nttProvider->disposeEntity( entity1 );
    nttProvider->disposeEntity( entity2 );
    nttProvider->disposeEntity( entity3 );
}