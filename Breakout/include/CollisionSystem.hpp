//
// Created by Lehdari on 4.12.2018.
//

#ifndef ECSTESTGAME_COLLISIONSYSTEM_HPP
#define ECSTESTGAME_COLLISIONSYSTEM_HPP


#include <ecs/System.hpp>
#include "PhysicsComponent.hpp"


namespace fug {

    class Ecs;
    class EventSystem;

} //namespace fug


FUG_SYSTEM(CollisionSubSystem, PhysicsComponent) {
public:
    friend class CollisionSystem;

    CollisionSubSystem(fug::EventSystem& eventSystem);

    void operator()(const fug::EntityId& eId, PhysicsComponent& phys);

private:
    fug::EventSystem&            _eventSystem;

    /// Pointers to references passed to parent CollisionSystem
    const fug::EntityId*    _parentEId;
    PhysicsComponent*       _parentPhys;
};


FUG_SYSTEM(CollisionSystem, PhysicsComponent) {
public:
    CollisionSystem(fug::Ecs& ecs, fug::EventSystem& eventSystem);

    void operator()(const fug::EntityId& eId, PhysicsComponent& phys);

private:
    fug::Ecs&                _ecs;
    CollisionSubSystem  _subSystem;
};


#endif //ECSTESTGAME_COLLISIONSYSTEM_HPP
