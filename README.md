# Asteroids

A small C++17 Asteroids game using OpenGL/GLUT for rendering and SFML Audio for sound.

## A personal note

This project was created for the Computer Graphics course during my Computer Science degree, as a way to put ideas about C++, graphics, input, movement, and collision detection into practice. It gradually became much more than an academic submission: a record of experimenting, debugging, and learning to turn separate concepts into a playable game. For that reason, this repository has considerable emotional value to me and remains a personal reminder of the curiosity, persistence, and enthusiasm that accompanied its creation.

## Layout

- `src/` — implementation files and the application entry point
- `include/` — project headers
- `assets/audio/` — sound effects
- `assets/data/` — game data, including the high-score file

## Build locally

Install CMake, a C++ compiler, FreeGLUT, OpenGL development headers, and SFML Audio.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
cd build && ./asteroids
```

The build copies `assets/` beside the executable, so run the game from the build directory.

The same workflow is available through Make:

```sh
make build
make run
make help
```

## Generate the Linux package

Docker is the only host requirement. It builds the Linux package in an isolated container.

```sh
make package-linux    # dist/linux/asteroids-linux-x86_64.zip
make package          # same as package-linux
```

The ZIP contains the executable, assets, and required bundled runtime libraries. Run `run-asteroids.sh` after extracting it; the script configures the bundled library path before launching the game.

[Download the latest Linux package](https://github.com/GSFranzoni/Asteroids/releases/latest/download/asteroids-linux-x86_64.zip).

## Linux package prerequisites

The Linux ZIP targets 64-bit Linux systems with an X11 display, working OpenGL drivers, and ALSA installed. ALSA is intentionally supplied by the host system so the game uses that system's audio configuration and output device.

Install the ALSA runtime if it is not already present:

```sh
# Debian / Ubuntu
sudo apt install libasound2

# Ubuntu 24.04 and newer, if the package above is unavailable
sudo apt install libasound2t64

# Fedora
sudo dnf install alsa-lib

# Arch Linux
sudo pacman -S alsa-lib
```

Extract and start the game from the directory containing the ZIP:

```sh
unzip asteroids-linux-x86_64.zip
./asteroids-linux-x86_64/run-asteroids.sh
```

The game will not run with audio in headless containers, remote sessions without audio forwarding, or systems with no accessible sound device.
