# TI4 Cartographer
![build and test](https://github.com/acodcha/ti4cartographer/workflows/build%20and%20test/badge.svg?branch=main)

Generates randomized balanced boards for the Twilight Imperium 4th Edition board game.

- [Setup](#setup)
- [Usage](#usage)
- [Board Layouts](#board-layouts)
- [Documentation](#documentation)
- [License](#license)
- [Maintainer](#maintainer)

## Setup
The following packages are required:
- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install with `sudo apt install cmake`.

Build the programs with:

```
mkdir build
cd build
cmake ..
make -j
```

This builds the main program, `build/bin/ti4cartographer`, as well as the `build/bin/ti4atlas` utility.
- `ti4cartographer` is the main program used to generate a randomized balanced board.
- `ti4atlas` is a small utility program that prints the various systems ranked from best to worst.

You can optionally run tests from the `build` directory with:

```
make test
```

You can optionally install the programs from the `build` directory with:

```
sudo make install
```

This installs the programs to `/usr/local/bin/ti4cartographer` and `/usr/local/bin/ti4atlas`. To uninstall a program, simply delete it.

[^ Back to Top](#ti4-cartographer)

## Usage
Run `ti4cartographer` with no arguments or with the `--help` argument to obtain usage information.

Otherwise, for regular use, run with:

```
ti4cartographer --players <number> [--version <type>] [--layout <type>] [--aggression <amount>] [--iterations <number>] [--quiet]
```

- `--players <number>`: Required. Choices are `2`, `3`, `4`, `5`, `6`, `7`, or `8`. Specifies the number of players.
- `--version <type>`: Optional. Choices are `base` or `expansion`. The default is `expansion`. Determines whether the system tiles from the Prophecy of Kings expansion can be used. Note that 7 and 8 player games require the expansion.
- `--layout <type>`: Optional. Choices vary by number of players, but typically include `regular`, `small`, or `large`; see the [Board Layouts](#board-layouts) section. The default is `regular`. Specifies the board layout.
- `--aggression <amount>`: Optional. Choices are `very-high`, `high`, `medium`, `low`, or `very-low`. The default is `medium`. Specifies the degree of expected aggression resulting from the placement of systems on the board. Higher aggression places better systems at equidistant positions compared to the systems in each player's slice, whereas lower aggression does the opposite.
- `--iterations <number>`: Optional. The default is `1000000`. Specifies the number of board layout iterations.
- `--quiet`: Optional. Activates quiet mode, where the only console output is the generated board's Tabletop Simulator string.

The program computes an optimal board given the arguments and outputs its Tabletop Simulator string as well as a link to visualize the board in Keegan Williams' TI4 Map Generator (<https://keeganw.github.io/ti4/>).

[^ Back to Top](#ti4-cartographer)

## Board Layouts
- [2 Players](#board-layout-2-players)
- [3 Players Regular](#board-layout-3-players-regular)
- [3 Players Small](#board-layout-3-players-small)
- [3 Players Large](#board-layout-3-players-large)
- [4 Players Regular](#board-layout-4-players-regular)
- [4 Players Large](#board-layout-4-players-large)
- [5 Players Regular](#board-layout-5-players-regular)
- [5 Players Small](#board-layout-5-players-small)
- [5 Players Large](#board-layout-5-players-large)
- [6 Players](#board-layout-6-players)
- [7 Players Regular](#board-layout-7-players-regular)
- [7 Players Large](#board-layout-7-players-large)
- [8 Players Regular](#board-layout-8-players-regular)
- [8 Players Large](#board-layout-8-players-large)

[^ Back to Top](#ti4-cartographer)

### Board Layout: 2 Players
4 planetary systems and 4 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 2
```

![2 Players](images/layouts/2_players.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 3 Players Regular
3 planetary systems and 2 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 3 --layout regular
```

![3 Players Regular](images/layouts/3_players_regular.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 3 Players Small
3 planetary systems and 2 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 3 --layout small
```

![3 Players Small](images/layouts/3_players_small.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 3 Players Large
4 planetary systems and 4 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 3 --layout large
```

![3 Players Large](images/layouts/3_players_large.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 4 Players Regular
3 planetary systems and 2 anomaly/wormhole/empty systems per player. Uses hyperlanes.

```
ti4cartographer --players 4 --layout regular
```

![4 Players Regular](images/layouts/4_players_regular.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 4 Players Large
3 planetary systems and 3 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 4 --layout large
```

![4 Players Large](images/layouts/4_players_large.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 5 Players Regular
3 planetary systems and 2 anomaly/wormhole/empty systems per player. Uses hyperlanes.

```
ti4cartographer --players 5 --layout regular
```

![5 Players Regular](images/layouts/5_players_regular.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 5 Players Small
3 planetary systems and 2 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 5 --layout small
```

![5 Players Small](images/layouts/5_players_small.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 5 Players Large
3 planetary systems and 3 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 5 --layout large
```

![5 Players Large](images/layouts/5_players_large.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 6 Players
3 planetary systems and 2 anomaly/wormhole/empty systems per player.

```
ti4cartographer --players 6
```

![6 Players](images/layouts/6_players.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 7 Players Regular
3 planetary systems and 2 anomaly/wormhole/empty systems per player. Uses hyperlanes.

```
ti4cartographer --players 7 --layout regular
```

![7 Players Regular](images/layouts/7_players_regular.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 7 Players Large
4 planetary systems and 2 anomaly/wormhole/empty systems per player. Uses hyperlanes.

```
ti4cartographer --players 7 --layout large
```

![7 Players Large](images/layouts/7_players_large.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 8 Players Regular
3 planetary systems and 2 anomaly/wormhole/empty systems per player. Uses hyperlanes.

```
ti4cartographer --players 8 --layout regular
```

![8 Players Regular](images/layouts/8_players_regular.png)

[^ Back to Board Layouts](#board-layouts)

### Board Layout: 8 Players Large
4 planetary systems and 2 anomaly/wormhole/empty systems per player. Uses hyperlanes.

```
ti4cartographer --players 8 --layout large
```

![8 Players Large](images/layouts/8_players_large.png)

[^ Back to Board Layouts](#board-layouts)

## Documentation
Building the documentation is optional and requires additional packages:
- **Doxygen:** On Ubuntu, install with `sudo apt install doxygen`.
- **Graphviz:** On Ubuntu, install with `sudo apt install graphviz`.
- **TeX Live:** On Ubuntu, install with `sudo apt install texlive texlive-fonts-extra`.

Documentation is disabled by default but can be generated from the `build` directory with:

```
cmake .. -DBUILD_DOCS=ON
make docs
```

This generates HTML documentation using Doxygen. The documentation is located in `docs/html`. Open the `docs/html/index.html` file in any web browser to view the documentation.

[^ Back to Top](#ti4-cartographer)

## License
This work is licensed under the MIT License. For more details, see the [LICENSE](LICENSE) file or <https://mit-license.org/>.

[^ Back to Top](#ti4-cartographer)

## Maintainer
- Alexandre Coderre-Chabot (<https://github.com/acodcha>)

[^ Back to Top](#ti4-cartographer)
