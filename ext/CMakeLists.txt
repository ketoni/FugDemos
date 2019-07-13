# Pull submodules
execute_process(COMMAND git submodule update --init)

add_subdirectory(fug)
add_subdirectory(vecmat)
