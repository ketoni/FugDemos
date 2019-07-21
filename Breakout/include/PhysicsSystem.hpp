//
// Created by lehdari on 3.11.2018.
//

#ifndef ECSTESTGAME_PHYSICSSYSTEM_HPP
#define ECSTESTGAME_PHYSICSSYSTEM_HPP


#include <ecs/System.hpp>
#include "PhysicsComponent.hpp"


FUG_SYSTEM(PhysicsSystem, PhysicsComponent) {
public:
    void operator()(const fug::EntityId& eId, PhysicsComponent& c);
};


#endif //ECSTESTGAME_PHYSICSSYSTEM_HPP
