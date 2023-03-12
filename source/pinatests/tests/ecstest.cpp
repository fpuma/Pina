#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <pina/ecs.h>

#include <pina/hidden/componentprovider.h>
#include <pina/hidden/entityprovider.h>

#include "testcomponents.h"

TEST( ECS, EntityLifetime )
{
    puma::pina::ECS ecs;
    puma::pina::EntityProvider* nttProvider = ecs.getEntityProvider();

    nttProvider->init( 20 );

    puma::pina::Entity ntt0 = nttProvider->requestEntity();
    puma::pina::Entity ntt1 = nttProvider->requestEntity();

#ifdef _DEBUG
    nttProvider->disposeEntity( ntt1 );
    nttProvider->uninit();
    EXPECT_DEATH(nttProvider->disposeEntity( ntt0 ), "EntityStatus::Unassigned" );
#else
    nttProvider->uninit();
    EXPECT_FALSE( nttProvider->isEntityEnabled( ntt0 ) );
    EXPECT_FALSE( nttProvider->isEntityEnabled( ntt1 ) );
#endif
}

TEST( ECS, EntityUsage )
{
    puma::pina::ECS ecs;
    puma::pina::EntityProvider* nttProvider = ecs.getEntityProvider();

    nttProvider->init( 20 );

    puma::pina::Entity ntt0 = nttProvider->requestEntity();
    puma::pina::Entity ntt1 = nttProvider->requestEntity();
    puma::pina::Entity ntt2 = nttProvider->requestEntity();

    EXPECT_TRUE( nttProvider->isEntityEnabled( ntt0 ) );
    EXPECT_TRUE( nttProvider->isEntityEnabled( ntt1 ) );
    EXPECT_TRUE( nttProvider->isEntityEnabled( ntt2 ) );

    nttProvider->disableEntity( ntt0 );
    nttProvider->disableEntity( ntt2 );

    EXPECT_FALSE( nttProvider->isEntityEnabled( ntt0 ) );
    EXPECT_TRUE( nttProvider->isEntityEnabled( ntt1 ) );
    EXPECT_FALSE( nttProvider->isEntityEnabled( ntt2 ) );

    nttProvider->disposeEntity(ntt0);
#ifdef _DEBUG
    EXPECT_DEATH( nttProvider->disposeEntity( ntt0 ) , "EntityStatus::Unassigned" );
#else
    nttProvider->disposeEntity( ntt0 );
#endif

    nttProvider->disposeEntity(ntt1);

#ifdef _DEBUG
    EXPECT_DEATH( nttProvider->isEntityEnabled( ntt1 ), "EntityStatus::Unassigned" );
#else
    EXPECT_FALSE( nttProvider->isEntityEnabled( ntt1 ) );
#endif

    nttProvider->uninit();

#ifdef _DEBUG
    EXPECT_DEATH( nttProvider->isEntityEnabled( ntt2 ), "EntityStatus::Unassigned" );
    EXPECT_DEATH( nttProvider->disposeEntity( ntt2 ), "EntityStatus::Unassigned" );
#else
    EXPECT_FALSE( nttProvider->isEntityEnabled( ntt2 ) );
    nttProvider->disposeEntity( ntt2 );
#endif

}

TEST( ECS, ComponentLifetime )
{
    puma::pina::ECS ecs;
    puma::pina::EntityProvider* nttProvider = ecs.getEntityProvider();
    puma::pina::ComponentProvider* compProvider = ecs.getComponentProvider();

    nttProvider->init( 20 );

    puma::pina::Entity ntt0 = nttProvider->requestEntity();
    puma::pina::Entity ntt1 = nttProvider->requestEntity();
    puma::pina::Entity ntt2 = nttProvider->requestEntity();

#ifdef _DEBUG
    EXPECT_DEATH( compProvider->add<ComponentA>( ntt0 ), "itRegisteredClass" );
    EXPECT_DEATH( compProvider->remove<ComponentA>( ntt0 ), "m_elements.end" );
    EXPECT_DEATH( compProvider->get<ComponentA>( ntt0 ), "m_elements.end" );
    EXPECT_DEATH( compProvider->getSafely<ComponentA>( ntt0 ), "m_elements.end" );
#else
    EXPECT_EQ( compProvider->add<ComponentA>( ntt0 ), nullptr );
    //compProvider->remove<ComponentA>( ntt0 ); //Why is this throwing an exception?
    EXPECT_EQ( compProvider->get<ComponentA>( ntt0 ), nullptr );
    EXPECT_EQ( compProvider->getSafely<ComponentA>( ntt0 ), nullptr );
#endif
    EXPECT_FALSE( compProvider->contains<ComponentA>( ntt0 ) );
    
    compProvider->registerClass<ComponentA>();
    compProvider->registerClass<ComponentB>();
    compProvider->registerClass<ComponentC>();

    EXPECT_FALSE( compProvider->contains<ComponentA>( ntt0 ) );
    EXPECT_FALSE( compProvider->contains<ComponentB>( ntt1 ) );
    EXPECT_FALSE( compProvider->contains<ComponentC>( ntt2 ) );

    compProvider->add<ComponentA>( ntt0 );
    compProvider->add<ComponentB>( ntt0 );

    compProvider->add<ComponentA>( ntt1 );
    compProvider->add<ComponentC>( ntt1 );

    compProvider->add<ComponentA>( ntt2 );
    compProvider->add<ComponentB>( ntt2 );
    compProvider->add<ComponentC>( ntt2 );

    EXPECT_TRUE( compProvider->contains<ComponentB>( ntt0 ) );
    EXPECT_TRUE( compProvider->contains<ComponentC>( ntt1 ) );
    EXPECT_TRUE( compProvider->contains<ComponentA>( ntt2 ) );

    auto safeCompA0 = compProvider->getSafely<ComponentA>( ntt0 );
    auto compA1 = compProvider->get<ComponentA>( ntt1 );
    auto compA2 = compProvider->get<ComponentA>( ntt2 );

    EXPECT_NE( safeCompA0, nullptr );
    EXPECT_NE( compA1, nullptr );
    EXPECT_NE( compA2, nullptr );

    compProvider->remove<ComponentA>( ntt1 );
    compProvider->remove<ComponentA>( ntt2 );

    EXPECT_FALSE( compProvider->contains<ComponentA>( ntt1 ) );
    EXPECT_FALSE( compProvider->contains<ComponentA>( ntt2 ) );

#ifdef _DEBUG
    EXPECT_DEATH( nttProvider->uninit(), "use_count" );
    safeCompA0.reset();
    nttProvider->uninit();
#else
    nttProvider->uninit();
#endif     
}

//TEST( ECS, Tests )
//{
//    puma::pina::ECS ecs;
//
//    puma::pina::EntityProvider* nttProvider = ecs.getEntityProvider();
//    puma::pina::ComponentProvider* componentProvider = ecs.getComponentProvider();
//    
//    componentProvider->registerClass<ComponentA>();
//    componentProvider->registerClass<ComponentB>();
//
//    puma::pina::Entity entity0 = nttProvider->requestEntity();
//
//#ifdef _DEBUG
//    EXPECT_DEATH( componentProvider->get<ComponentA>( entity0 ), "itElement != m_elements.end" );
//#else
//    EXPECT_EQ( nullptr, componentProvider->get<ComponentA>( entity0 ) );
//#endif
//
//    EXPECT_FALSE( componentProvider->contains<ComponentA>( entity0 ) );
//
//    std::shared_ptr<ComponentA> ca0 = componentProvider->add<ComponentA>( entity0 );
//
//    EXPECT_NE( nullptr, ca0 );
//
//    puma::pina::Entity entity1 = nttProvider->requestEntity();
//    puma::pina::Entity entity2 = nttProvider->requestEntity();
//    puma::pina::Entity entity3 = nttProvider->requestEntity();
//
//    auto ca1 = componentProvider->add<ComponentA>( entity1 );
//
//    auto ca2 = componentProvider->add<ComponentA>( entity2 );
//    auto cb2 = componentProvider->add<ComponentB>( entity2 );
//
//    auto cb3 = componentProvider->add<ComponentB>( entity3 );
//
//    //EXPECT_EQ( 1, ca0->getNumber() );
//
//    //EXPECT_EQ( 2, ca0->getNumber() );
//    //EXPECT_EQ( 1, ca1->getNumber() );
//    //EXPECT_EQ( 1, ca2->getNumber() );
//
//    //EXPECT_EQ( 2, ca0->getNumber() );
//    //EXPECT_EQ( 1, ca1->getNumber() );
//    //EXPECT_EQ( 1, ca2->getNumber() );
//    //EXPECT_EQ( 1, cb2->getNumber() );
//    //EXPECT_EQ( 1, cb3->getNumber() );
//
//    nttProvider->disableEntity( entity2 );
//    //EXPECT_FALSE( ca2->isEnabled() );
//    //EXPECT_FALSE( cb2->isEnabled() );
//
//    nttProvider->enableEntity( entity2 );
//
//    EXPECT_TRUE( ca2->isEnabled() );
//    EXPECT_TRUE( cb2->isEnabled() );
//
//    //EXPECT_EQ( 2, ca2->getNumber() );
//    //EXPECT_EQ( 2, cb2->getNumber() );
//
//
//    //ENTITIES BY COMPONENTS
//    auto ntts = ecs.getEntitesByComponents<ComponentA, ComponentB>();
//    //EXPECT_EQ( ntts.size(), 1 );
//    //EXPECT_EQ( *ntts.begin(), entity2);
//
//    componentProvider->add<ComponentA>( entity3 );
//    ntts = ecs.getEntitesByComponents<ComponentA, ComponentB>();
//
//    //EXPECT_EQ( ntts.size(), 2 );
//    auto nttsBegin = ntts.begin();
//    //EXPECT_EQ( *nttsBegin, entity2 );
//    //std::advance( nttsBegin, 1 );
//    //EXPECT_EQ( *nttsBegin, entity3 );
//
//
//    //UNINIT
//    componentProvider->remove<ComponentA>( entity0 );
//    componentProvider->remove<ComponentA>( entity1 );
//    componentProvider->remove<ComponentA>( entity2 );
//    componentProvider->remove<ComponentB>( entity2 );
//    componentProvider->remove<ComponentA>( entity3 );
//    componentProvider->remove<ComponentB>( entity3 );
//
//    nttProvider->disposeEntity( entity0 );
//    nttProvider->disposeEntity( entity1 );
//    nttProvider->disposeEntity( entity2 );
//    nttProvider->disposeEntity( entity3 );
//}