//
// Created by lehdari on 3.11.2018.
//

#ifndef ECSTESTGAME_PHYSICSCOMPONENT_HPP
#define ECSTESTGAME_PHYSICSCOMPONENT_HPP


#include <ecs/Ecs.hpp>
#include <vec2f.h>

#include "CollisionVolume.hpp"


struct PhysicsComponent {
    PhysicsComponent(vm::vec2f pos, vm::vec2f vel,
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


FUG_DECLARE_COMPONENT_TEMPLATES(PhysicsComponent);


#endif //ECSTESTGAME_PHYSICSCOMPONENT_HPP
