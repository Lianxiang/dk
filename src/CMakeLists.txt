cmake_minimum_required(VERSION 2.8)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS on)

project(dk)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_C_FLAGS "-g -O3 -Wall")

set(SERVER_SRC_FILES
        cmds.c
        collect.c
        fight.c
        item.c
        make.c
        meditate.c
        msg.c
        practice.c
        room.c
        server.c
        user.c
        world.c
        cmds/chat.c
        cmds/help.c
        cmds/quit.c
        cmds/who.c
)

add_executable(server ${SERVER_SRC_FILES})
target_link_libraries(server event)

set(CLIENT_SRC_FILES
        client.c
)

add_executable(client ${CLIENT_SRC_FILES})
target_link_libraries(client event)
