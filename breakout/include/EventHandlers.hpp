//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_EVENTHANDLERS_HPP
#define ECSTESTGAME_EVENTHANDLERS_HPP


#include <vector>
#include <engine/EventHandler.hpp>

#include "CollisionEvent.hpp"
#include "Logics.hpp"


FUG_EVENT_HANDLER(EventHandler_Block_CollisionEvent, CollisionEvent);
FUG_EVENT_HANDLER(EventHandler_Ball_CollisionEvent, CollisionEvent);

struct LaunchEvent {};
FUG_EVENT_LOGIC_HANDLER(EventHandler_Ball_LaunchEvent, LaunchEvent, Logic_Ball);


#endif //ECSTESTGAME_EVENTHANDLERS_HPP
