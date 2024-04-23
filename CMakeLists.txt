cmake_minimum_required(VERSION 3.27)
project(raylib_space_invaders C CXX)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME raylib_space_invaders)

file(GLOB SOURCES *.c *.cpp *.h *.hpp src/*.c src/*.cpp src/*.h src/*.hpp src/*/*.c src/*/*.cpp src/*/*.h src/*/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCES})


# because of raylib - TODO(hector) - make this only for debug builds, figure out
#  why this is even needed.
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# uncomment if not using spdlog below, as spdlog uses fmt
#find_package(fmt CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
