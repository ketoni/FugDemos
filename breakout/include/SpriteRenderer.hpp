#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "PhysicsComponent.hpp"
#include "SpriteComponent.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>

FUG_SYSTEM(SpriteRenderer, PhysicsComponent, SpriteComponent) {
    SpriteRenderer(sf::RenderWindow& window) : window(window) { };
    void operator()(const fug::EntityId& eId, PhysicsComponent& phys, SpriteComponent &sprite)
    {
        sprite.sprite.setPosition(phys.pos.x, phys.pos.y);
        window.draw(sprite.sprite);
    }
    sf::RenderWindow& window;
};

#endif
