# Magyar Kartya

This game is modelled after the Hungarian cardgame Magyar Kartya. It has a singleplayer and a pure Peer-to-Peer multiplayer. It is written in C++17 and utilizes OpenGL in form of SFML.


### Contributing
This project is currently using a Windows specific library and is therefore limited only to users with access to the Win32 API.

### Building on Windows
1. Download the appropriate version of SFML(64bit) from [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/).
2. Clone this repository by running `git clone https://github.com/jbar98/Magyar-Kartya.git` inside your shell.
3. Navigate to the previously cloned repository and edit the path to SFML and if necessary also the path to your Windows libaries inside the CMakeLists.txt.
4. Run `mkdir build && cd build && cmake ..` inside your shell.
5. Copy-paste all files from the bin folder of your SFML installation (typically located at SFML-VERSION-COMPILER_SPECIFIC/SFML-VERSION/bin) to the 
in step 4 created "build" directory.
6. Finally navigate to the "build" directory inside your shell and compile by running `cmake --build .`.

### Building on Linux
1. Get the SFML libraries from your package manager. On Debian-based distros for example, run `sudo apt install libsfml-dev` inside your shell.
2. Clone this repository by running `git clone https://github.com/jbar98/Magyar-Kartya.git`.
3. Navigate to the cloned repository and switch to the linux branch by running `git checkout linux`.
4. Now run `mkdir build && cd build` followed by `cmake ..` and compile by running `cmake --build .`.
