# Game Engine

![](https://img.shields.io/badge/Build-passing-brightgreen) ![https://www.libsdl.org](https://img.shields.io/badge/SDL-SDL2-blue) [![GitHub Repo stars](https://img.shields.io/github/stars/unpwnabl/Game-Engine)](https://github.com/unpwnabl/Game-Engine/stargazers) ![License](https://img.shields.io/github/license/unpwnabl/Game-Engine)
</br>
A game engine written in C++ with [SDL2](https://www.libsdl.org), using the least possible libraries before it breaks (or I break). 

![](/imgs/screenshot.png)

## Installation

To install, download all of the files from the [github repository](https://www.github.com/unpwnabl/Game-Engine) into your local machine at any desired path:
```bash
git pull https://github.com/unpwnabl/Game-Engine
cd Game-Engine
```

## Run

To run the program, make the `build.sh` file executable and build:
```bash
chmod +x build.sh
./build.sh
```
For more informations, use the option `./build.sh --help` or `./build.sh -h`.

> [!IMPORTANT]
> To install dependencies, run `chmod +x dependencies.sh && sudo ./dependencies.sh` to install automatically.

> [!CAUTION]
> Some elements, like fonts and images, are omitted due to their licenses not being public. Thus, running the program without them will lead to problems.

## Wiki

For more informations regarding functionalities, please refer to the [wiki](wiki.md).

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
This project is licensed under the [GPL-3.0 License](https://www.gnu.org/licenses/gpl-3.0.html).
