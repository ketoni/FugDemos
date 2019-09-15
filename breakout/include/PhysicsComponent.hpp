//
// Created by lehdari on 3.11.2018.
//

#ifndef ECSTESTGAME_PHYSICSCOMPONENT_HPP
#define ECSTESTGAME_PHYSICSCOMPONENT_HPP


#include <ecs/Ecs.hpp>
#include <vecmat/vec2f.h>

#include "CollisionVolume.hpp"


struct PhysicsComponent {
    PhysicsComponent(vm::vec2f pos = vm::vec2f(0.0f, 0.0f),
                     vm::vec2f vel = vm::vec2f(0.0f, 0.0f),
                     const CollisionVolume& colVol = CollisionVolume()) :
        pos     (pos),
        vel     (vel),
        colVol  (colVol)
    {
    }

    vm::vec2f       pos;
    vm::vec2f       vel;
    CollisionVolume colVol;
};


#endif //ECSTESTGAME_PHYSICSCOMPONENT_HPP
