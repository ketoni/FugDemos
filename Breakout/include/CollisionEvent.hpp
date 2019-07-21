//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_COLLISIONEVENT_HPP
#define ECSTESTGAME_COLLISIONEVENT_HPP


#include <engine/EventTypeId.hpp>
#include <utils/Types.hpp>
#include <vecmat/vec2f.h>


struct CollisionEvent {
    fug::EntityId    entityId;
    vm::vec2f   normal;

    CollisionEvent(const fug::EntityId& eId,
                   const vm::vec2f& normal = vm::vec2f(0.0f, 0.0f)) :
        entityId    (eId),
        normal      (normal)
    {}
};


FUG_DECLARE_EVENT_TEMPLATES(CollisionEvent);


#endif //ECSTESTGAME_COLLISIONEVENT_HPP
