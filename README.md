# Project Levenshtein

by Jonathan Chevelu
jonathan.chevelu@enssat.fr

©ENSSAT 2020

## Dependencies

Needed:

* C++ compiler (tested on GCC 8.4; Clang 10.0)
* CMake (tested on 3.00)
* Doxygen (tested on 1.8)
* Boost (programm optionused only but need install all - To be fixed) (tested on 1.71)

```sh
sudo apt install cmake g++ libboost-all-dev
```

Recommended (for debug):

* Valgrind
* Massif-visualizer

```sh
sudo apt install valgrind massif-visualizer
```

## Installation

Use Cmake or the build.sh script as a generic short cut.
It is recommended to read all provided options using:

```sh
./build.sh --help
```

For a local install:

```sh
./build.sh
```

For system wide install (may need administrator privileges):

```sh
./build.sh --install
```

## Run

See ./bin/levenshtein

```sh
./bin/levenshtein --w1 "Le petit chat" --w2 "Les chats sont petits"
```

## Examples

* Lev("chien","niches") = 4
* Lev("Le petit chat","Les chats sont petits") = 14
* Lev("Le petit chat est gentil mais sauvage. Je l'aime quand meme. Et vous ? Les aimez-vous ?Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.","Les chats sont petits et voraces mais c'est pour cela qu'ils sont mignons. Et vous ? Les aimez-vous ? Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.") = 56

## Uninstall

```sh
./build.sh --uninstall
./build.sh --clear
```

The later commande remove building objects.
