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

    auto safeCompA0 = compProvider->getSafely<ComponentA>( ntt0 );
    auto compA2 = compProvider->get<ComponentA>( ntt2 );
    auto compB2 = compProvider->get<ComponentB>( ntt2 );

    EXPECT_TRUE( compA2->isEnabled() );
    EXPECT_TRUE( compB2->isEnabled() );

    nttProvider->disableEntity( ntt2 );
    EXPECT_FALSE( compA2->isEnabled() );
    EXPECT_FALSE( compB2->isEnabled() );

    nttProvider->enableEntity( ntt2 );
    EXPECT_TRUE( compA2->isEnabled() );
    EXPECT_TRUE( compB2->isEnabled() );

    compA2->disable();
    EXPECT_FALSE( compA2->isEnabled() );
    EXPECT_TRUE( compB2->isEnabled() );

#ifdef _DEBUG
    EXPECT_DEATH( nttProvider->enableEntity( ntt2 ), "EntityStatus::Enabled" );
#endif

    nttProvider->disableEntity( ntt2 );
    EXPECT_FALSE( compA2->isEnabled() );
    EXPECT_FALSE( compB2->isEnabled() );

#ifdef _DEBUG
    EXPECT_DEATH( nttProvider->disableEntity( ntt2 ), "EntityStatus::Disabled" );
#endif

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

TEST( ECS, DynamicFetching )
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