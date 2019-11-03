//
// Created by Lehdari on 6.4.2019.
//

#ifndef ECSTESTGAME_LOGICS_HPP
#define ECSTESTGAME_LOGICS_HPP


#include <engine/Logic.hpp>
#include <graphics/SpriteSheet.hpp>


FUG_LOGIC(Logic_Ball) {
    Logic_Ball(const fug::EntityId& paddleId);

    void operator()(fug::Ecs& ecs, const fug::EntityId& eId);

    fug::EntityId    _paddleId;
    bool        _followPaddle;
};

FUG_LOGIC(Logic_Paddle) {
    void operator()(fug::Ecs& ecs, const fug::EntityId& eId);
};

FUG_LOGIC(Logic_GameManager) {
    Logic_GameManager(fug::SpriteSheet *blockSheet);

    void operator()(fug::Ecs& ecs, const fug::EntityId& eId);

    fug::SpriteSheet *_blockSheet;
    int64_t      _points;
    int64_t      _lives;
};


#endif //ECSTESTGAME_LOGICS_HPP

