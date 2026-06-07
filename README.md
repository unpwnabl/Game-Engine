# Game Engine

![](https://img.shields.io/badge/Build-passing-brightgreen) ![https://www.libsdl.org](https://img.shields.io/badge/SDL-SDL2-blue) [![GitHub Repo stars](https://img.shields.io/github/stars/unpwnabl/Game-Engine)](https://github.com/unpwnabl/Game-Engine/stargazers) ![License](https://img.shields.io/github/license/unpwnabl/Game-Engine)
</br>

<p align="center">
    A game engine written in C++ with [SDL2](https://www.libsdl.org), using the least possible libraries before it breaks (or I break). 
</p>

<p align="center">
    [Getting Started](#gs) | [Wiki](#wiki) | [Contributing](#cont) | [License](#license)
</p>

![](/imgs/screenshot.png) <a name="install"></a>

## Getting Started <a name="gs"></a>

### Installation

To install, download all of the files from the [github repository](https://www.github.com/unpwnabl/Game-Engine) into your local machine at any desired path:
```bash
git pull https://github.com/unpwnabl/Game-Engine
cd Game-Engine
```

### Run <a name="run"></a>

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

## Wiki <a name="wiki"></a>

For more informations regarding functionalities, please refer to the [wiki](wiki.md).

## Contributing <a name="cont"></a>

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
Please make sure to update tests as appropriate.

## License <a name="license"></a>
This project is licensed under the [GPL-3.0 License](https://www.gnu.org/licenses/gpl-3.0.html).
