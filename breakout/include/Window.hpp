//
// Created by Lehdari on 29.9.2018.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#include <SDL.h>
#include <ecs/Ecs.hpp>
#include <engine/EventSystem.hpp>
#include <engine/LogicSystem.hpp>
#include <graphics/SpriteDrawBufferSingleton.hpp>
#include <graphics/SpriteDrawComponent.hpp>
#include <graphics/SpriteSheet.hpp>

#include "PhysicsSystem.hpp"
#include "CollisionSystem.hpp"
#include "EntityIdSingleton.hpp"
#include "SystemSingleton.hpp"


class Window {
public:
    struct Settings {
        std::string windowName;
        uint32_t    width;
        uint32_t    height;
        bool        vsync;

        Settings(const std::string& windowName = "",
                 uint32_t width = 800,
                 uint32_t height = 600,
                 bool vsync = true) :
             windowName (windowName),
             width      (width),
             height     (height),
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
    bool                _running = true;

    fug::Ecs            _ecs;
    fug::EventSystem    _eventSystem;
    PhysicsSystem       _physicsSystem;
    CollisionSystem     _collisionSystem;
    fug::LogicSystem    _logicSystem;

    GLuint            _spriteProg;
    glsprite_renderer _spriteRenderer;

    fug::SpriteSheet _blockSheet;
    fug::SpriteSheet _ballSheet;
    fug::SpriteSheet _paddleSheet;

    void handleEvents(SDL_Event &event);
    void runSystems(void);
    void render(void);
};


#endif	//	TYPES_HPP
