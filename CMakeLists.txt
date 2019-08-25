cmake_minimum_required(VERSION 3.13.0)

project (MagyarKartya LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

if (MSVC)
    # set path to libraries
    set(SFML_DIR D:/Libs/SFML/SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/lib/cmake/SFML)
    include_directories(C:/Program Files \(x86\)/Windows Kits/10/Lib/10.0.17763.0/um/x86)

elseif(MINGW)
    set(SFML_DIR D:/Libs/SFML/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML)
    include_directories(C:/Program Files \(x86\)/Windows Kits/10/Lib/10.0.17763.0/um/x86)
endif()


find_package(SFML COMPONENTS graphics window network system)

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
    src/windowSettings.cpp
    src/get_user_path.cpp)

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


if (MSVC)
    target_link_libraries(MagyarKartya
        sfml-graphics
        sfml-audio
        sfml-network
        sfml-system
        UserEnv)

elseif (MINGW)
    target_link_libraries(MagyarKartya
            stdc++fs
            sfml-graphics
            sfml-audio
            sfml-network
            sfml-system
            UserEnv)

elseif (UNIX AND NOT APPLE)
    target_link_libraries(MagyarKartya
        pthread
        stdc++fs 	
        sfml-graphics
        sfml-audio
        sfml-network
        sfml-system)
endif()
