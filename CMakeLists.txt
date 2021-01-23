cmake_minimum_required(VERSION 3.10.0)
project (MagyarKartya LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)


if(WIN32)
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)

        set(SFML_DIR D:/Libs/SFML/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML)
        include_directories(C:/Program Files \(x86\)/Windows Kits/10/Lib/10.0.17763.0/um/x86)
        message("detected GNU on windows")
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL msvc)
        # set path to libraries
        set(SFML_DIR D:/Libs/SFML/SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/lib/cmake/SFML)
        include_directories(C:/Program Files \(x86\)/Windows Kits/10/Lib/10.0.17763.0/um/x86)
        message("detected msvc/clang on windows")
    endif()
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

target_link_libraries(MagyarKartya
                    PRIVATE
                    sfml-graphics
                    sfml-audio
                    sfml-network
                    sfml-system)


if (WIN32)
    #mingw
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        target_link_libraries(MagyarKartya
                PRIVATE 
                stdc++fs
                UserEnv)
    #clang on windows
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
        target_link_libraries(MagyarKartya
                        PRIVATE
                        UserEnv
                            )
        target_compile_options(MagyarKartya PRIVATE -Wall -Wextra -fcolor-diagnostics)
    #windows
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL msvc)
        target_link_libraries(MagyarKartya
                        PRIVATE
                        UserEnv
                            )
    endif()
    
    #linux
elseif (UNIX AND NOT APPLE)
    target_link_libraries(MagyarKartya
        PRIVATE
        pthread
        stdc++fs 	
    )

endif()

if (WIN32)
    #copy dlls

    if (CMAKE_BUILD_TYPE STREQUAL Release)
        add_custom_command(TARGET MagyarKartya PRE_BUILD        # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
                "${SFML_DIR}/../../../bin/openal32.dll"
                "${SFML_DIR}/../../../bin/sfml-audio-2.dll"
                "${SFML_DIR}/../../../bin/sfml-graphics-2.dll"
                "${SFML_DIR}/../../../bin/sfml-network-2.dll"
                "${SFML_DIR}/../../../bin/sfml-system-2.dll"
                "${SFML_DIR}/../../../bin/sfml-window-2.dll"
                $<TARGET_FILE_DIR:MagyarKartya>) 
    endif()
                

    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        add_custom_command(TARGET MagyarKartya PRE_BUILD       # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
                "${SFML_DIR}/../../../bin/openal32.dll"
                "${SFML_DIR}/../../../bin/sfml-audio-d-2.dll"
                "${SFML_DIR}/../../../bin/sfml-graphics-d-2.dll"
                "${SFML_DIR}/../../../bin/sfml-network-d-2.dll"
                "${SFML_DIR}/../../../bin/sfml-system-d-2.dll"
                "${SFML_DIR}/../../../bin/sfml-window-d-2.dll"
                $<TARGET_FILE_DIR:MagyarKartya>) 
    endif()
endif()

install(TARGETS MagyarKartya
    RUNTIME DESTINATION bin
    )

install(DIRECTORY resources
    DESTINATION .
    )
