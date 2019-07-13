//
// Created by Lehdari on 29.9.2018.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#include <SDL.h>
#include <ecs/Ecs.hpp>
#include <engine/EventSystem.hpp>
#include <engine/LogicSystem.hpp>

#include "PhysicsSystem.hpp"
#include "SpriteComponent.hpp"
#include "SpriteRenderer.hpp"
#include "CollisionSystem.hpp"


class Window {
public:
    struct Settings {
        std::string     windowName;
        uint32_t        resolution[2];
        bool            vsync

        Settings(const std::string& windowName = "",
                 const uint32_t resolution = {800, 600},
                 const bool vsync = true) :
             windowName (windowName),
             videoMode  (videoMode),
             vsync      (vsync)
        {}
    };

    Window(const Settings& settings = Settings());
    ~Window();

    Window(const Window&) = delete;
    const Window& operator=(const Window&) = delete;

    void loop(void);

private:
    Settings            _settings;
    SDL_Window*         _window;
    SDL_GLContext       _glContext;

    fug::Ecs            _ecs;
    fug::EventSystem    _eventSystem;
    PhysicsSystem       _physicsSystem;
    SpriteRenderer      _spriteRenderer;
    CollisionSystem     _collisionSystem;
    fug::LogicSystem    _logicSystem;

    sf::Texture _blockTexture;
    sf::Texture _ballTexture;

    uint64_t _playerId;
    uint64_t _ballId;

    void handleEvents(sf::Event& event);
    void runSystems(void);
    void render(void);
};


#endif	//	TYPES_HPP
