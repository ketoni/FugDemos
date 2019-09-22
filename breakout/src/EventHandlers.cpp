//
// Created by Lehdari on 9.1.2019.
//

#include <EventHandlers.hpp>
#include <ecs/Ecs.hpp>
#include <engine/EventComponent.hpp>
#include <CollisionEvent.hpp>
#include <PhysicsComponent.hpp>
#include <SpriteComponent.hpp>
#include <SystemSingleton.hpp>


FUG_DEFINE_EVENT_TEMPLATES(LaunchEvent);
FUG_DEFINE_EVENT_TEMPLATES(BreakEvent);
FUG_DEFINE_EVENT_TEMPLATES(LoseLifeEvent);


using namespace fug;


void EventHandler_Block_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
    auto* sc = ecs.getSingleton<SystemSingleton>();
    sc->eventSystem->broadcastEvent(BreakEvent());

    ecs.removeEntity(eId);
}

void EventHandler_Ball_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
    auto* phys = ecs.getComponent<PhysicsComponent>(eId);
    phys->vel = 2.0f*dot(event.normal, -phys->vel)*event.normal+phys->vel;
}

void EventHandler_BottomWall_CollisionEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, const CollisionEvent& event)
{
    auto* sc = ecs.getSingleton<SystemSingleton>();
    sc->eventSystem->broadcastEvent(LoseLifeEvent());
}

void EventHandler_Ball_LaunchEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, Logic_Ball& logic, const LaunchEvent& event)
{
    if (logic._followPaddle) {
        ecs.getComponent<PhysicsComponent>(eId)->vel = vm::vec2f(2.0f, -5.0f);
        logic._followPaddle = false;
    }
}

void EventHandler_GameManager_BreakEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, Logic_GameManager& logic,
    const BreakEvent& event)
{
    ++logic._points;
}

void EventHandler_GameManager_LoseLifeEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, Logic_GameManager& logic,
    const LoseLifeEvent& event)
{
    if (logic._lives > 0) {
        --logic._lives;
    }
    else {
        logic._lives = 3;
        logic._points = 0;

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 5; ++j) {
                uint64_t id = i * 8 + j + 7;

                if (ecs.entityExists(id))
                    continue;

                ecs.setComponent(id, PhysicsComponent(
                    vm::vec2f(176 + i * 64, 64 + j * 32), vm::vec2f(0.0f, 0.0f),
                    CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
                ecs.setComponent(id, SpriteComponent(logic._blockTexture, (i ^ j) % 4, 64, 32));
                ecs.getComponent<SpriteComponent>(id)->sprite.setOrigin(32, 16);

                ecs.getComponent<EventComponent>(id);
                ecs.getComponent<EventComponent>(id)->addHandler<EventHandler_Block_CollisionEvent>();
            }
        }
    }
}

void EventHandler_Ball_LoseLifeEvent::handleEvent(
    Ecs& ecs, const EntityId& eId, Logic_Ball& logic,
    const LoseLifeEvent& event)
{
    logic._followPaddle = true;
    auto* pc = ecs.getComponent<PhysicsComponent>(eId);
    pc->pos.x = ecs.getComponent<PhysicsComponent>(logic._paddleId)->pos.x;
    pc->pos.y = 518;
    pc->vel = vm::vec2f(0.0f, 0.0f);
}
