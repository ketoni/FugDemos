//
// Created by Lehdari on 6.4.2019.
//

#include <Logics.hpp>
#include <PhysicsComponent.hpp>
#include <ecs/Ecs.hpp>
#include <iostream>
#include <sstream>
#include <SDL.h>


using namespace fug;


Logic_Ball::Logic_Ball(const EntityId& paddleId) :
    _paddleId       (paddleId),
    _followPaddle   (true)
{
}

void Logic_Ball::operator()(Ecs& ecs, const EntityId& eId)
{
    if (_followPaddle) {
        auto* myPc = ecs.getComponent<PhysicsComponent>(eId);
        auto* paddlePc = ecs.getComponent<PhysicsComponent>(_paddleId);
        myPc->pos.x = paddlePc->pos.x;
    }
}


void Logic_Paddle::operator()(Ecs& ecs, const EntityId& eId)
{
    auto* pc = ecs.getComponent<PhysicsComponent>(eId);
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT] && pc->pos.x > 32.0f)
        pc->pos.x -= 4.0f;
    if (keys[SDL_SCANCODE_RIGHT] && pc->pos.x < 800.0f-32.0f)
        pc->pos.x += 4.0f;
}

Logic_GameManager::Logic_GameManager(fug::SpriteSheet *blockSheet) :
    _blockSheet(blockSheet),
    _points (0),
    _lives  (3)
{ }

void Logic_GameManager::operator()(Ecs& ecs, const EntityId& eId)
{
    std::stringstream text;
    text << "Lives: " << _lives << "\tPoints: " << _points;
    std::cout << "\r" << text.str() << std::flush;
}
