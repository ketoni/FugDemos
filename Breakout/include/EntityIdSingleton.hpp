//
// Created by Lehdari on 17.4.2019.
//

#ifndef ECSTESTGAME_ENTITYIDSINGLETON_HPP
#define ECSTESTGAME_ENTITYIDSINGLETON_HPP


#include <ecs/Ecs.hpp>


struct EntityIdSingleton {
    uint64_t    paddleId;
    uint64_t    ballId;
    uint64_t    gameManagerId;
};


FUG_DECLARE_COMPONENT_TEMPLATES(EntityIdComponent);


#endif //ECSTESTGAME_ENTITYIDSINGLETON_HPP
