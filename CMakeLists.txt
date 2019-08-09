cmake_minimum_required(VERSION 3.14.0)

project (MagyarKartya LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

# set path to SFML's cmake config files
set(SFML_DIR D:/Libs/SFML/SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML COMPONENTS graphics window network system)

include_directories(C:/Program Files \(x86\)/Windows Kits/10/Lib/10.0.17763.0/um/x86)

set(CMAKE_COMPILER_)

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
    src/Card.hpp
    src/Client.hpp
    src/Deck.hpp
    src/Enemy.hpp
    src/Host.hpp
    src/Logic.hpp
    src/OnlineEnemy.hpp
    src/OnlinePlayer.hpp
    src/OnlineUser.hpp
    src/Player.hpp
    src/ReturnCodes.hpp
    src/textureArray.hpp
    src/TextureHandler.hpp
    src/windowSettings.hpp)

add_executable(MagyarKartya ${project_sources} ${project_headers})

target_link_libraries(MagyarKartya
        sfml-graphics
        sfml-audio
        sfml-network
        sfml-system
        UserEnv)