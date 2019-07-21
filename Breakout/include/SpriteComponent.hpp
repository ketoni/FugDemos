#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP


#include <ecs/Ecs.hpp>
#include <SFML/Graphics/Sprite.hpp>


struct SpriteComponent {
    SpriteComponent(sf::Texture &texture, int idx, int w, int h) :
        idx(idx)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(idx * w, 0, w, h));
    }
    int idx;
    sf::Sprite sprite;
};


FUG_DECLARE_COMPONENT_TEMPLATES(SpriteComponent);


#endif
