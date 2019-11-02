#ifndef SPRITEDRAWBUFFERGENERATOR_HPP
#define SPRITEDRAWBUFFERGENERATOR_HPP

#include <ecs/Ecs.hpp>
#include <ecs/System.hpp>
#include <graphics/SpriteDrawComponent.hpp>

#include "PhysicsComponent.hpp"


FUG_SYSTEM(SpriteDrawBufferGenerator, PhysicsComponent, fug::SpriteDrawComponent) {
public:
    SpriteDrawBufferGenerator(fug::Ecs& ecs) : _ecs(ecs) {}
    void operator()(const fug::EntityId& eId, PhysicsComponent& phys,
                    const fug::SpriteDrawComponent &spriteDraw);

private:
    fug::Ecs& _ecs;
};

#endif
