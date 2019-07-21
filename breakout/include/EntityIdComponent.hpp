//
// Created by Lehdari on 17.4.2019.
//

#ifndef ECSTESTGAME_ENTITYIDCOMPONENT_HPP
#define ECSTESTGAME_ENTITYIDCOMPONENT_HPP


#include <ecs/Ecs.hpp>


struct EntityIdComponent {
    uint64_t    paddleId;
    uint64_t    ballId;
    uint64_t    gameManagerId;
};


FUG_DECLARE_COMPONENT_TEMPLATES(EntityIdComponent);


#endif //ECSTESTGAME_ENTITYIDCOMPONENT_HPP
