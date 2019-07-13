cmake_minimum_required(VERSION 3.0)
project(FugDemos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(ext)
add_subdirectory(breakout)

# Find and link SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(Breakout 
    ${BREAKOUT_SOURCES}
)

target_include_directories(Breakout
    PUBLIC
        breakout/include
        ext/fug/include
        ext/vecmat
)

target_link_libraries(Breakout
    PUBLIC
        fug_ecs
        fug_engine
        vecmat
        sfml-system
        sfml-window
        sfml-graphics
)

target_compile_definitions(Breakout
    PRIVATE
        RES_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/breakout"
)
