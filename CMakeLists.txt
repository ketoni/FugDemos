cmake_minimum_required(VERSION 3.0)
project(FugDemos)


#Target to build
set(FUGDEMOS_TARGET "Breakout" CACHE STRING "Demo project to build")


#Set required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Output libraries to same directory with binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#Name of the target directory
string(TOLOWER ${FUGDEMOS_TARGET} FUGDEMOS_TARGET_DIRECTORY)


#Scan files of target to build
add_subdirectory(${FUGDEMOS_TARGET_DIRECTORY})


#Breakout target
if ("${FUGDEMOS_TARGET}" STREQUAL "Breakout")
    #Add application headers to FUG_APP_HEADERS for auto-scanning
    set(FUG_APP_HEADERS ${FUG_APP_HEADERS}
        ${BREAKOUT_HEADERS}
    )

    #List types for fug type-id system (see ext/fug/cmake/*_types.cmake for details)
    #Note: Not required when using the auto-scan feature
    set(FUG_APP_COMPONENT_TYPES "PhysicsComponent SpriteComponent")
    set(FUG_APP_SINGLETON_TYPES "EntityIdSingleton SystemSingleton")

    #Add external dependencies
    add_subdirectory(ext)


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

endif()
