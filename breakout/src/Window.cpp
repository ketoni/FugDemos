//
// Created by Lehdari on 29.9.2018.
//

#include <Window.hpp>
#include <engine/LogicComponent.hpp>
#include <PhysicsComponent.hpp>
#include <EventHandlers.hpp>
#include <Logics.hpp>
#include <EntityIdSingleton.hpp>
#include <SystemSingleton.hpp>
#include <glutil.h>


using namespace fug;

static void checkSDLError(int line = -1)
{
    const char *error = SDL_GetError();
    if (*error != '\0') {
        printf(" Window.cpp line: %i\n", line);
        printf("SDL Error: %s\n", error);
        SDL_ClearError();
    }
}

Window::Window(const Window::Settings &settings) :
    _settings           (settings),
    _eventSystem        (_ecs),
    _collisionSystem    (_ecs, _eventSystem),
    _logicSystem        (_ecs)
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    _window = SDL_CreateWindow(
        _settings.windowName.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _settings.width,
        _settings.height,
        SDL_WINDOW_OPENGL
    );
    if (!_window)
        throw std::runtime_error("Failed to create SDL window");
    checkSDLError(__LINE__);

    _glContext = SDL_GL_CreateContext(_window);
    checkSDLError(__LINE__);

    if (gl3wInit())
        throw std::runtime_error("gl3wInit failed");

    if (_settings.vsync) {
        SDL_GL_SetSwapInterval(1);
        checkSDLError(__LINE__);
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);

    _blockSheet.load(RES_DIRECTORY "/res/gfx/blocks.png", 256, 32, 64, 32, 0);
    _ballSheet.load(RES_DIRECTORY "/res/gfx/ball.png", 32, 32, 32, 32, 0);

    auto* eIdComp = _ecs.getSingleton<EntityIdSingleton>();
    auto& paddleId = eIdComp->paddleId;
    auto& ballId = eIdComp->ballId;
    auto& gameManagerId = eIdComp->gameManagerId;
    paddleId = 0;
    ballId = 1;
    gameManagerId = 2;

    auto* sComp = _ecs.getSingleton<SystemSingleton>();
    sComp->physicsSystem = std::make_unique<PhysicsSystem>();
    sComp->eventSystem = std::make_unique<EventSystem>(_ecs);
    sComp->logicSystem = std::make_unique<LogicSystem>(_ecs);
    sComp->collisionSystem = std::make_unique<CollisionSystem>(_ecs, *sComp->eventSystem);
    sComp->spriteDrawBufferGenerator = std::make_unique<SpriteDrawBufferGenerator>(_ecs);

    /* Renderer */

    // TODO: Full paths
    GLuint vs_id = glutil_compile_shader_file("../ext/fug/ext/glsprite/shader/vs.glsl", GL_VERTEX_SHADER);
    assert(vs_id);
    GLuint fs_id = glutil_compile_shader_file("../ext/fug/ext/glsprite/shader/fs.glsl", GL_FRAGMENT_SHADER);
    assert(fs_id);
    _spriteProg = glutil_link_shaders(glCreateProgram(), vs_id, fs_id);
    assert(_spriteProg);

    glDeleteShader(fs_id);
    glDeleteShader(vs_id);

    int err = glsprite_renderer_init(&_spriteRenderer, _spriteProg,
                                     _settings.width, _settings.height);
    assert(err == 0);

    /* Player */
    _ecs.setComponent(paddleId, PhysicsComponent(
        vm::vec2f(400, 550), vm::vec2f(0.0, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
    _ecs.setComponent(paddleId, SpriteDrawComponent(&_blockSheet, vm::vec2i(3, 0), vm::vec2f(32, 16)));
    _ecs.addComponent<LogicComponent>(paddleId)->addLogic<Logic_Paddle>();

    /* Ball */
    _ecs.setComponent(ballId, PhysicsComponent(
        vm::vec2f(400, 518), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::CIRCLE, 16.0f)));
    _ecs.setComponent(ballId, SpriteDrawComponent(&_ballSheet, vm::vec2i(0, 0), vm::vec2f(16, 16)));
    _ecs.addComponent<EventComponent>(ballId)->addHandler<EventHandler_Ball_CollisionEvent>();
    _ecs.getComponent<EventComponent>(ballId)->addHandler<EventHandler_Ball_LaunchEvent>();
    _ecs.getComponent<EventComponent>(ballId)->addHandler<EventHandler_Ball_LoseLifeEvent>();
    _ecs.addComponent<LogicComponent>(ballId)->addLogic<Logic_Ball>(paddleId);

    /* Game Manager */
    _ecs.addComponent<LogicComponent>(gameManagerId)->
        addLogic<Logic_GameManager>(&_blockSheet);
    _ecs.addComponent<EventComponent>(gameManagerId)->
        addHandler<EventHandler_GameManager_BreakEvent>();
    _ecs.addComponent<EventComponent>(gameManagerId)->
        addHandler<EventHandler_GameManager_LoseLifeEvent>();

    /* Walls */
    _ecs.setComponent(3, PhysicsComponent(
        vm::vec2f(-16, 300), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 332.0f)));
    _ecs.setComponent(4, PhysicsComponent(
        vm::vec2f(816, 300), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -16.0f, -300.0f, 16.0f, 332.0f)));
    _ecs.setComponent(5, PhysicsComponent(
        vm::vec2f(400, -16), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));
    _ecs.setComponent(6, PhysicsComponent(
        vm::vec2f(400, 648), vm::vec2f(0.0f, 0.0f),
        CollisionVolume(CollisionVolume::BOX, -400.0f, -16.0f, 400.0f, 16.0f)));
    _ecs.addComponent<EventComponent>(6)->addHandler<EventHandler_BottomWall_CollisionEvent>();

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            uint64_t id = i * 8 + j + 7;
            _ecs.setComponent(id, PhysicsComponent(
                vm::vec2f(176 + i * 64, 64 + j * 32), vm::vec2f(0.0f, 0.0f),
                CollisionVolume(CollisionVolume::BOX, -32.0f, -16.0f, 32.0f, 16.0f)));
            _ecs.setComponent(id, SpriteDrawComponent(&_blockSheet, vm::vec2i((i ^ j) % 4, 0), vm::vec2f(32, 16)));

            _ecs.addComponent<EventComponent>(id)->addHandler<EventHandler_Block_CollisionEvent>();
        }
    }
}

Window::~Window()
{
    glsprite_renderer_destroy(&_spriteRenderer);
    glDeleteProgram(_spriteProg);
    SDL_GL_DeleteContext(_glContext);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Window::loop(void)
{
    while (_running)
    {
        runSystems();
        render();

        // Event processing
        SDL_Event event;
        while (SDL_PollEvent(&event))
            handleEvents(event);

    }
}

void Window::handleEvents(SDL_Event &event)
{
    static auto* eIdComp = _ecs.getSingleton<EntityIdSingleton>();
    static auto& ballId = eIdComp->ballId;

    static auto* sComp = _ecs.getSingleton<SystemSingleton>();
    static auto& eventSystem = *sComp->eventSystem;

    switch (event.type) {
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                _running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        _running = false;
                        break;

                    case SDLK_SPACE:
                        eventSystem.sendEvent(ballId, LaunchEvent());

                    default:
                        break;
                }
            }
            break;

        default:
            break;
    }
}

void Window::runSystems(void)
{
    static auto* sComp = _ecs.getSingleton<SystemSingleton>();
    static auto& physicsSystem = *sComp->physicsSystem;
    static auto& collisionSystem = *sComp->collisionSystem;
    static auto& spriteDrawBufferGenerator = *sComp->spriteDrawBufferGenerator;
    static auto& eventSystem = *sComp->eventSystem;
    static auto& logicSystem = *sComp->logicSystem;

    // TODO: Move to DrawBufferGenerator::pre
    auto* drawBuffers = _ecs.getSingleton<fug::SpriteDrawBufferSingleton>();
    for (auto& [texID, buffer] : drawBuffers->buffers)
        glsprite_draw_buffer_clear(&buffer);
    _ecs.getSingleton<fug::SpriteDrawBufferSingleton>()->buffers.clear();

    _ecs.runSystem(physicsSystem);
    _ecs.runSystem(spriteDrawBufferGenerator);
    _ecs.runSystem(collisionSystem);
    _ecs.runSystem(logicSystem);
    while (eventSystem.swap())
        _ecs.runSystem(eventSystem);
}

void Window::render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto* drawBuffers = _ecs.getSingleton<fug::SpriteDrawBufferSingleton>();
    for (auto& [texID, buffer] : drawBuffers->buffers)
        glsprite_render_draw_buffer(&_spriteRenderer, &buffer);

    SDL_GL_SwapWindow(_window);
}
