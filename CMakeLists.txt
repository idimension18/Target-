cmake_minimum_required(VERSION 3.20)
project(Target__)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SDL2_INCLUDE_DIR SDL2/include)
set(SDL2_LIBRARIES SDL2/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARIES})

set(SOURCE_FILES src/main.cpp)
add_executable(Target__ src/main.cpp src/Ship.cpp src/Ship.h src/Laser.cpp src/Laser.h src/Target.cpp src/Target.h src/Asteroide.cpp src/Asteroide.h src/Sprite.cpp src/Sprite.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_mixer SDL2_image)