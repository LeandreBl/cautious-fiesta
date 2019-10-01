cmake_minimum_required (VERSION 3.1.0)

project("cautious-fiesta" CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HDRS "include/*.hpp")

SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -g3 -Wall -Wextra -Weffc++ -Wshadow -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wsign-conversion -Wlogical-op -Wuseless-cast -fsanitize=address")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -g3 -Wextra -O3 -fsanitize=address")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

find_package(Boost 1.71)

add_subdirectory(sfml-scene)
add_subdirectory(discord-rpc)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
add_executable("cautious-fiesta" ${SRCS} ${HDRS})
target_include_directories("cautious-fiesta" PRIVATE "./include" ${Boost_INCLUDE_DIRS} "sfml-scene/include" "discord-rpc/include")
target_link_libraries("cautious-fiesta" asan ${Boost_LIBRARIES} stdc++fs sfml-scene sfml-graphics sfml-window sfml-audio sfml-system sfml-network discord-rpc)
