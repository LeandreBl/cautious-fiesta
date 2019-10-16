cmake_minimum_required (VERSION 3.7)

project("cautious-fiesta" CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HDRS "include/*.hpp")
file(GLOB_RECURSE MENUSRCS "src/mainMenu/*.cpp")
file(GLOB_RECURSE MENUHDRS "include/mainMenu/*.hpp")
file(GLOB_RECURSE ROOMSRCS "src/roomMenu/*.cpp")
file(GLOB_RECURSE ROOMHDRS "include/roomMenu/*.hpp")

SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -g3 -Wall -Wextra -Weffc++ -Wshadow -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wsign-conversion -Wlogical-op -Wuseless-cast -fsanitize=address")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -g3 -Wextra -O3 -fsanitize=address")

add_subdirectory(sfml-scene)
add_subdirectory(discord-rpc)

add_executable("cautious-fiesta" ${SRCS} ${HDRS} ${MENUSRCS} ${MENUHDRS} ${ROOMSRCS} ${ROOMHDRS})
target_include_directories("cautious-fiesta" PRIVATE "./include" "./include/mainMenu" "./include/roomMenu" "sfml-scene/include" "discord-rpc/include")
target_link_libraries("cautious-fiesta" sfml-graphics sfml-system sfml-window sfml-network sfml-audio asan stdc++fs sfml-scene discord-rpc)
