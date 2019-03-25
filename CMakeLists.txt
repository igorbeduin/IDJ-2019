cmake_minimum_required (VERSION 2.6)
project (IDJ)

add_definitions(-std=c++11)

set(SDL2_INCLUDE /usr/include/SDL2)

include_directories (
    include/
    $(SDL2_INCLUDE)
)

add_executable(IDJ
    src/Main.cpp
    src/Game.cpp
    src/Music.cpp
    src/Sprite.cpp
    src/State.cpp
)

target_link_libraries(IDJ SDL2 SDL2_image SDL2_mixer SDL2_ttf)