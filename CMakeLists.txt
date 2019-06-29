cmake_minimum_required(VERSION 3.15.0)

project (MagyarKartya LANGUAGES CXX)

find_package(SFML COMPONENTS graphics window network system)

include_directories(C:/Program Files (x86)/Windows Kits/10/Lib/10.0.17763.0/um/x86)


set(project_sources 
    src/Card.cpp
    src/Client.cpp
    src/Deck.cpp
    src/Enemy.cpp
    src/gameMenu.cpp
    src/Host.cpp
    src/Logic.cpp
    src/main.cpp
    src/multiplayer.cpp
    src/multiplayerSetup.cpp
    src/OnlineEnemy.cpp
    src/OnlinePlayer.cpp
    src/OnlineUser.cpp
    src/Player.cpp
    src/singleplayer.cpp
    src/singleplayerSetup.cpp
    src/textureArray.cpp
    src/TextureHandler.cpp
    src/windowSettings.cpp)

set(project_headers
    src/headers/Card.hpp
    src/headers/Client.hpp
    src/headers/Deck.hpp
    src/headers/Enemy.hpp
    src/headers/Host.hpp
    src/headers/Logic.hpp
    src/headers/OnlineEnemy.hpp
    src/headers/OnlinePlayer.hpp
    src/headers/OnlineUser.hpp
    src/headers/Player.hpp
    src/headers/ReturnCodes.hpp
    src/headers/textureArray.hpp
    src/headers/TextureHandler.hpp
    src/headers/windowSettings.hpp)

add_executable(${PROJECT_NAME} ${project_sources} ${project_headers})

target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-audio
    sfml-network
    sfml-system
    UserEnv)




