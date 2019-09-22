//
// Created by Lehdari on 29.9.2018.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <ecs/Ecs.hpp>
#include <engine/EventSystem.hpp>
#include <engine/LogicSystem.hpp>

#include "PhysicsSystem.hpp"
#include "SpriteComponent.hpp"
#include "SpriteRenderer.hpp"
#include "CollisionSystem.hpp"
#include "EntityIdSingleton.hpp"
#include "SystemSingleton.hpp"
#include "GameStateSingleton.hpp"


class Window {
public:
    struct Settings {
        std::string     windowName;
        sf::VideoMode   videoMode;
        int64_t         framerateLimit;

        Settings(const std::string& windowName = "",
                 const sf::VideoMode& videoMode = sf::VideoMode(800, 600),
                 int64_t framerateLimit = 60) :
             windowName     (windowName),
             videoMode      (videoMode),
             framerateLimit (framerateLimit)
        {}
    };

    Window(const Settings& settings = Settings());

    void loop(void);

private:
    Settings            _settings;
    sf::RenderWindow    _window;

    fug::Ecs            _ecs;
    fug::EventSystem    _eventSystem;
    PhysicsSystem       _physicsSystem;
    SpriteRenderer      _spriteRenderer;
    CollisionSystem     _collisionSystem;
    fug::LogicSystem    _logicSystem;

    sf::Texture _blockTexture;
    sf::Texture _ballTexture;

    void handleEvents(sf::Event& event);
    void runSystems(void);
    void render(void);
};


#endif	//	TYPES_HPP
