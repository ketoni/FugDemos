//
// Created by Lehdari on 9.1.2019.
//

#ifndef ECSTESTGAME_EVENTHANDLERS_HPP
#define ECSTESTGAME_EVENTHANDLERS_HPP


#include <vector>
#include <engine/EventHandler.hpp>
#include <engine/EventTypeId.hpp>

#include "CollisionEvent.hpp"
#include "Logics.hpp"


FUG_EVENT_HANDLER(EventHandler_Block_CollisionEvent, CollisionEvent);
FUG_EVENT_HANDLER(EventHandler_Ball_CollisionEvent, CollisionEvent);
FUG_EVENT_HANDLER(EventHandler_BottomWall_CollisionEvent, CollisionEvent);

struct LaunchEvent {};
FUG_DECLARE_EVENT_TEMPLATES(LaunchEvent);
FUG_EVENT_LOGIC_HANDLER(EventHandler_Ball_LaunchEvent, LaunchEvent, Logic_Ball);

struct BreakEvent {};
FUG_DECLARE_EVENT_TEMPLATES(BreakEvent);
FUG_EVENT_LOGIC_HANDLER(EventHandler_GameManager_BreakEvent, BreakEvent, Logic_GameManager);

struct LoseLifeEvent {};
FUG_DECLARE_EVENT_TEMPLATES(LoseLifeEvent);
FUG_EVENT_LOGIC_HANDLER(
    EventHandler_GameManager_LoseLifeEvent,
    LoseLifeEvent, Logic_GameManager);
FUG_EVENT_LOGIC_HANDLER(
    EventHandler_Ball_LoseLifeEvent,
    LoseLifeEvent, Logic_Ball);


#endif //ECSTESTGAME_EVENTHANDLERS_HPP
