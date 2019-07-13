//
// Created by Lehdari on 29.9.2018.
//

#include <Window.hpp>
#include <engine/LogicComponent.hpp>
#include <PhysicsComponent.hpp>
#include <EventHandlers.hpp>
#include <Logics.hpp>


using namespace fug;

static void checkSDLError(int line = -1)
{
    const char *error = SDL_GetError();
    if (*error != '\0') {
        printf("SDL Error: %s\n", error);
        if (line != -1)
            printf(" + line: %i\n", line);
        SDL_ClearError();
    }
}


Window::Window(const Window::Settings &settings) :
    _settings           (settings),
    _playerId           (0),
    _ballId             (1),
    _eventSystem        (_ecs),
    _collisionSystem    (_ecs, _eventSystem),
    _logicSystem        (_ecs)
{
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow(
        _settings.windowName,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _settings.resolution[0],
        _settings.resolution[1],
        SDL_WINDOW_OPENGL
    );
    if (!_window)
        throw std::runtime_error("Failed to create SDL window");
    checkSDLError(__LINE__);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    _glContext = SDL_GL_CreateContext(_window);
    checkSDLError(__LINE__);

    if (_settings.vsync) {
        SDL_GL_SetSwapInterval(1);
        checkSDLError(__LINE__);
    }

    _blockTexture.loadFromFile(RES_DIRECTORY "/res/gfx/blocks.png");
    _ballTexture.loadFromFile(RES_DIRECTORY "/res/gfx/ball.png");

    /* Player */
    _ecs.addComponent(_playerId, PhysicsComponent(
        vm::vec2f(400, 550), vm::vec2f(0.0, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
    _ecs.addComponent(_playerId, SpriteComponent(_blockTexture, 3, 64, 32));
    _ecs.getComponent<SpriteComponent>(_playerId)->sprite.setOrigin(32, 16);
    _ecs.addComponent(_playerId, LogicComponent());
    _ecs.getComponent<LogicComponent>(_playerId)->addLogic<Logic_Paddle>();

    /* Ball */
    _ecs.addComponent(_ballId, PhysicsComponent(
        vm::vec2f(400, 518), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::CIRCLE, 16.0f)));
    _ecs.addComponent(_ballId, SpriteComponent(_ballTexture, 0, 32, 32));
    _ecs.getComponent<SpriteComponent>(_ballId)->sprite.setOrigin(16, 16);
    _ecs.addComponent(_ballId, EventComponent());
    _ecs.getComponent<EventComponent>(_ballId)->addHandler<EventHandler_Ball_CollisionEvent>();
    _ecs.getComponent<EventComponent>(_ballId)->addHandler<EventHandler_Ball_LaunchEvent>();
    _ecs.addComponent(_ballId, LogicComponent());
    _ecs.getComponent<LogicComponent>(_ballId)->addLogic<Logic_Ball>(_playerId);

    /* Walls */
    _ecs.addComponent(2, PhysicsComponent(
        vm::vec2f(-16, 300), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 300.0f)));
    _ecs.addComponent(3, PhysicsComponent(
        vm::vec2f(816, 300), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 300.0f)));
    _ecs.addComponent(4, PhysicsComponent(
        vm::vec2f(400, -16), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));
    _ecs.addComponent(5, PhysicsComponent(
        vm::vec2f(400, 616), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            uint64_t id = i * 8 + j + 6;
            _ecs.addComponent(id, PhysicsComponent(
                vm::vec2f(176 + i * 64, 64 + j * 32), vm::vec2f(0.0f, 0.0f),
                CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
            _ecs.addComponent(id, SpriteComponent(_blockTexture, (i ^ j) % 4, 64, 32));
            _ecs.getComponent<SpriteComponent>(id)->sprite.setOrigin(32, 16);

            _ecs.addComponent(id, EventComponent());
            _ecs.getComponent<EventComponent>(id)->addHandler<EventHandler_Block_CollisionEvent>();
        }
    }
}

Window::~Window()
{
    SDL_DeleteContext(_glContext);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Window::loop(void)
{
    _window.setActive();
    while (_window.isOpen())
    {
        // Event processing
        SDL_Event event;
        while (SDL_PollEvent(&event))
            handleEvents(event);

        runSystems();
        render();

        SDL_GL_SwapWindow(_window);
    }
}

void Window::handleEvents(SDL_Event &event)
{
    switch (event.type) {
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                _window.close();
            break;

        case SDL_KEYDOWN:
            switch (event.keysym.sym) {
                case SDLK_ESCAPE:
                    _window.close();
                    break;

                case SDLK_SPACE:
                    _eventSystem.sendEvent(_ballId, LaunchEvent());
            }
            break;

        default:
            break;
    }
}

void Window::runSystems(void)
{
    _ecs.runSystem(_physicsSystem);
    _ecs.runSystem(_spriteRenderer);
    _ecs.runSystem(_collisionSystem);
    _ecs.runSystem(_eventSystem);
    _ecs.runSystem(_logicSystem);

    _eventSystem.clear();
}

void Window::render(void)
{
    //  Render OpenGL stuff here
}
