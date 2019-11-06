cmake_minimum_required (VERSION 3.7)

project("cautious-fiesta" CXX)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0.0")
    message(FATAL_ERROR "Insufficient gcc version")
  endif()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SRCS "src/*.cpp")

set(HDRS_DIRS "include/" "include/Game" "include/mainMenu" "include/roomMenu")

SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -g3 -Wall -Wextra -Weffc++ -Wshadow -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wsign-conversion -Wlogical-op -Wuseless-cast -fsanitize=address")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -g3 -Wextra -O3 -fsanitize=address")

add_subdirectory(cautious-fiesta-common)

include_directories(
	"cautious-fiesta-common/include"
	"cautious-fiesta-common/sfml-scene/include"
	"cautious-fiesta-common/discord-rpc/include"
)

add_executable("cautious-fiesta" ${SRCS} ${HDRS})
target_include_directories("cautious-fiesta" PRIVATE ${HDRS_DIRS})
target_link_libraries("cautious-fiesta" cautious-fiesta-common sfml-graphics sfml-system sfml-window sfml-network sfml-audio asan stdc++fs sfml-scene discord-rpc stdc++fs)
