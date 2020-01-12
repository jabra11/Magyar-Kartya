# Magyar Kartya

This game is modelled after the Hungarian cardgame Magyar Kartya. 
You can play against the computer or against a friend using the peer-to-peer based multiplayer.

![Annotation 2019-08-25 211101](https://user-images.githubusercontent.com/34109209/63654652-71776400-c77d-11e9-8a60-55efae82aec6.png)



### Contributing
I initially started this project to get more comfortable with [SFML](https://www.sfml-dev.org/) and the language itself, therefore most of the code can be improved easily. It is written in C++17.

It can be built on Windows and Linux. Build instructions are below.

### Building on Windows
1. Download the appropriate version of SFML(64bit) from [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/).
2. Clone this repository by running `git clone https://github.com/jbar98/Magyar-Kartya.git` inside your shell.
3. Navigate to the previously cloned repository and edit the path to SFML and if necessary also the path to your Windows libaries inside the CMakeLists.txt.
4. Run `mkdir build && cd build && cmake ..` inside your shell.
5. Copy-paste all files from the "bin" directory of your SFML installation (typically located at SFML-VERSION-COMPILER_SPECIFIC/SFML-VERSION/bin) to the 
in step 4 created "build" directory.
6. Finally navigate to the "build" directory and compile by running `cmake --build .` inside your shell.

### Building on Linux
1. Get the SFML libraries from your package manager. On Debian-based distros for example, run `sudo apt install libsfml-dev` inside your shell.
2. Clone this repository by running `git clone https://github.com/jbar98/Magyar-Kartya.git`.
3. Now navigate to the cloned repository and run `mkdir build && cd build` followed by `cmake ..` and compile by running `cmake --build .`.
