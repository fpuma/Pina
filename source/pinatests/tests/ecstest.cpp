#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    
    EXPECT_FALSE( compProvider->contains<ComponentA>( ntt1 ) );

    nttProvider->disposeEntity( ntt2 );

    EXPECT_FALSE( compProvider->contains<ComponentA>( ntt2 ) );
    EXPECT_FALSE( compProvider->contains<ComponentB>( ntt2 ) );
    EXPECT_FALSE( compProvider->contains<ComponentC>( ntt2 ) );


#ifdef _DEBUG
    EXPECT_DEATH( compProvider->get<ComponentA>( ntt2 ), "m_elements.end" );
    EXPECT_DEATH( nttProvider->uninit(), "use_count" );
    safeCompA0.reset();
    nttProvider->uninit();
#else
    compA2 = compProvider->get<ComponentA>( ntt2 );
    EXPECT_EQ( compA2, nullptr );
    nttProvider->uninit();
#endif     
}

TEST( ECS, ComponentsUsage )
{
    puma::pina::ECS ecs;
    puma::pina::EntityProvider* nttProvider = ecs.getEntityProvider();
    puma::pina::ComponentProvider* compProvider = ecs.getComponentProvider();

    nttProvider->init( 20 );

    puma::pina::Entity ntt0 = nttProvider->requestEntity();
    puma::pina::Entity ntt1 = nttProvider->requestEntity();
    puma::pina::Entity ntt2 = nttProvider->requestEntity();

    compProvider->registerClass<ComponentA>();
    compProvider->registerClass<ComponentB>();
    compProvider->registerClass<ComponentC>();

    compProvider->add<ComponentA>( ntt0 );
    compProvider->add<ComponentB>( ntt0 );

    compProvider->add<ComponentA>( ntt1 );
    compProvider->add<ComponentC>( ntt1 );

    compProvider->add<ComponentA>( ntt2 );
    compProvider->add<ComponentB>( ntt2 );
    compProvider->add<ComponentC>( ntt2 );

    auto aNtts = ecs.getEntitesByComponents<ComponentA>();
    auto abNtts = ecs.getEntitesByComponents<ComponentA, ComponentB>();
    auto acNtts = ecs.getEntitesByComponents<ComponentA, ComponentC>();
    auto abcNtts = ecs.getEntitesByComponents<ComponentA, ComponentB, ComponentC>();

    EXPECT_EQ( aNtts.size(), 3 );
    EXPECT_EQ( abNtts.size(), 2 );
    EXPECT_EQ( acNtts.size(), 2 );
    EXPECT_EQ( abcNtts.size(), 1 );

    for (const puma::pina::Entity& ntt : abNtts)
    {
        EXPECT_TRUE( ntt.value() == 0 || ntt.value() == 2 );
    }

    for (const puma::pina::Entity& ntt : acNtts)
    {
        EXPECT_TRUE( ntt.value() == 1 || ntt.value() == 2 );
    }

    EXPECT_TRUE( abcNtts.begin()->value() == 2 );

    compProvider->remove<ComponentA>( ntt2 );

    abcNtts = ecs.getEntitesByComponents<ComponentA, ComponentB, ComponentC>();
    auto bcNtts = ecs.getEntitesByComponents<ComponentB, ComponentC>();

    EXPECT_TRUE( abcNtts.empty() );
    EXPECT_EQ( bcNtts.size(), 1 );

    EXPECT_TRUE( bcNtts.begin()->value() == 2 );

    nttProvider->uninit();

}