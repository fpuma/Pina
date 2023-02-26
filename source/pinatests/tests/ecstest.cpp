#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <pina/ecs.h>
#include "testsystems.h"

TEST( ECS, Tests )
{
    puma::pina::ECS ecs;

    ecs.initEntities();
    ecs.initComponents();
    ecs.initSystems( std::make_unique<TestSystemProvider>(ecs.getEcsData()) );

    puma::pina::EntityProvider* nttProvider = ecs.getEntityProvider();
    puma::pina::ComponentProvider* componentProvider = ecs.getComponentProvider();
    TestSystemProvider* systemProvider = static_cast<TestSystemProvider*>(ecs.getSystemProvider());

    systemProvider->registerSystem<SystemA>();
    systemProvider->registerSystem<SystemB>();

    componentProvider->registerComponent<ComponentA>();
    componentProvider->registerComponent<ComponentB>();

    puma::pina::Entity entity0 = nttProvider->requestEntity();

#ifdef _DEBUG
    EXPECT_DEATH( componentProvider->getComponent<ComponentA>( entity0 ), "itElement != m_elements.end" );
#else
    EXPECT_EQ( nullptr, componentProvider->getComponent<ComponentA>( entity0 ) );
#endif

    EXPECT_FALSE( componentProvider->containsComponent<ComponentA>( entity0 ) );

    std::shared_ptr<ComponentA> ca0 = componentProvider->addComponent<ComponentA>( entity0 );

    EXPECT_NE( nullptr, ca0 );

    puma::pina::Entity entity1 = nttProvider->requestEntity();
    puma::pina::Entity entity2 = nttProvider->requestEntity();
    puma::pina::Entity entity3 = nttProvider->requestEntity();

    auto ca1 = componentProvider->addComponent<ComponentA>( entity1 );

    auto ca2 = componentProvider->addComponent<ComponentA>( entity2 );
    auto cb2 = componentProvider->addComponent<ComponentB>( entity2 );

    auto cb3 = componentProvider->addComponent<ComponentB>( entity3 );

    auto systemA = systemProvider->addSystem<SystemA>();
    auto systemB = systemProvider->addSystem<SystemB>();

    EXPECT_NE( nullptr, systemA );
    EXPECT_NE( nullptr, systemB );

    systemA->registerEntity( entity0 );

    systemA->update( *nttProvider, *componentProvider );
    EXPECT_EQ( 1, ca0->getNumber() );

    systemA->registerEntity( entity1 );
    systemA->registerEntity( entity2 );
    systemA->update( *nttProvider, *componentProvider );
    EXPECT_EQ( 2, ca0->getNumber() );
    EXPECT_EQ( 1, ca1->getNumber() );
    EXPECT_EQ( 1, ca2->getNumber() );

    systemB->registerEntity( entity2 );
    systemB->registerEntity( entity3 );
    systemB->update( *nttProvider, *componentProvider );
    EXPECT_EQ( 2, ca0->getNumber() );
    EXPECT_EQ( 1, ca1->getNumber() );
    EXPECT_EQ( 1, ca2->getNumber() );
    EXPECT_EQ( 1, cb2->getNumber() );
    EXPECT_EQ( 1, cb3->getNumber() );

    nttProvider->disableEntity( entity2 );
    EXPECT_FALSE( ca2->isEnabled() );
    EXPECT_FALSE( cb2->isEnabled() );

    nttProvider->enableEntity( entity2 );

    EXPECT_TRUE( ca2->isEnabled() );
    EXPECT_TRUE( cb2->isEnabled() );

    systemProvider->update( *nttProvider, *componentProvider );

    EXPECT_EQ( 2, ca2->getNumber() );
    EXPECT_EQ( 2, cb2->getNumber() );


    //ENTITIES BY COMPONENTS
    auto ntts = componentProvider->getEntitesByComponents<ComponentA, ComponentB>();
    EXPECT_EQ( ntts.size(), 1 );
    EXPECT_EQ( *ntts.begin(), entity2);

    componentProvider->addComponent<ComponentA>( entity3 );
    ntts = componentProvider->getEntitesByComponents<ComponentA, ComponentB>();

    EXPECT_EQ( ntts.size(), 2 );
    auto nttsBegin = ntts.begin();
    EXPECT_EQ( *nttsBegin, entity2 );
    std::advance( nttsBegin, 1 );
    EXPECT_EQ( *nttsBegin, entity3 );


    //UNINIT
    componentProvider->removeComponent<ComponentA>( entity0 );
    componentProvider->removeComponent<ComponentA>( entity1 );
    componentProvider->removeComponent<ComponentA>( entity2 );
    componentProvider->removeComponent<ComponentB>( entity2 );
    componentProvider->removeComponent<ComponentA>( entity3 );
    componentProvider->removeComponent<ComponentB>( entity3 );

    nttProvider->disposeEntity( entity0 );
    nttProvider->disposeEntity( entity1 );
    nttProvider->disposeEntity( entity2 );
    nttProvider->disposeEntity( entity3 );

    systemProvider->removeSystem<SystemA>();
    systemProvider->removeSystem<SystemB>();
}