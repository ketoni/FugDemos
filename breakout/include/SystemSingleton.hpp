//
// Created by Lehdari on 17.4.2019.
//

#ifndef ECSTESTGAME_SYSTEMSINGLETON_HPP
#define ECSTESTGAME_SYSTEMSINGLETON_HPP


#include <ecs/Ecs.hpp>
#include <engine/EventSystem.hpp>
#include <engine/LogicSystem.hpp>
#include <PhysicsSystem.hpp>
#include <CollisionSystem.hpp>
#include <SpriteDrawBufferGenerator.hpp>
#include <memory>


/// SystemComponent is a singleton component containing all the systems used
struct SystemSingleton {
    std::unique_ptr<PhysicsSystem>      physicsSystem;
    std::unique_ptr<CollisionSystem>    collisionSystem;
    std::unique_ptr<SpriteDrawBufferGenerator> spriteDrawBufferGenerator;
    std::unique_ptr<fug::EventSystem>        eventSystem;
    std::unique_ptr<fug::LogicSystem>        logicSystem;
};


#endif //ECSTESTGAME_SYSTEMSINGLETON_HPP
