# Game Engine

## Structure

- Core
	- [UI](#ui)
		- [Window](#window)
		- [Renderer](#renderer)
		- [Text](#text)
	- [Miscellaneous](#misc)
		- [Split](#split)
		- [FPS](#fps)
		- [Error](#error)
		- [Colors](#colors)
	- Audio
	- Images 
- Platform

## Functionalities

### UI <a name="ui"></a>

Everything concerning the creation/destruction of windows, renderers, text, images, etc.. is here. The User-Interface is subdivided into these sections:

#### Window <a name="window"></a>

- `void create_window(SDL_Window*& window, const char* title, int x, int y, int width, int height)`: creates a window, with title `title`, of size `w`\*`h` at (`x,y`). By default, `x` and `y` are `SDL_WINDOWPOS_CENTERED`, and size is 960\*540.
- `void destroy_window(SDL_Window*& window)`: destroys the `window` and deals with the clean up of memory.

#### Renderer <a name="renderer"></a>

- `void create_renderer(SDL_Window* window, SDL_Renderer*& renderer)`: creates a new renderer for the selected `window`, with `SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED` on.
- `void render_rect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color)`: renders a rectangle on a specified `renderer`, with a determined color. 
- `void renderer_update(SDL_Renderer* renderer)`: updated the renderer on each frame.
- `void renderer_clear(SDL_Renderer* renderer)`: clears the renderer on each frame.
- `void destroy_renderer(SDL_Renderer*& renderer)`: destroys the given `renderer` and deals with the clean up of memory.

#### Text <a name="text"></a>

- `void init_ttf()`: initializes the `SDL_ttf` library. Also, opens a dummy font to check if everything works correctly, and immediately closes it.
- `void render_text(SDL_Renderer* renderer, const char* s, TTF_Font *font, int x, int y, int scale, SDL_Color fore)`: renders text `s` into the given `renderer`, using the `font` at the position (`x,y`) with size `scale` and color `fore`.
	- `void generate_text(SDL_Renderer* renderer, const char* s, TTF_Font* font, int x, int y, int scale, SDL_Color fore)`: parent function, takes in an array of characters `s`, creates a `SDL_Surface` from the `renderer` and then creates a `SDL_Texture` in which a rectangle holds the text. If the array of characters `s` is longer than a set maximum length of $max\_len = k * (W_{width} / sclale)$, where $k$ is the size of a single character, $W_{width}$ is the width of the window, and $scale$ is the size of the text to be rendered, it is split into chunks and then rendered one by one, using an offset.
- `void close_ttf()`: closes the `SDL_ttf` library and deals with the clean up of memory.

### Misc <a name="misc"></a>

The functionalities that aren't specific to one field, and multi-purpose, are here. These include:

#### Split <a name="split"></a>

- `std::vector<const char*> split(const char* s, size_t max_len)`: splits an array of characters `s` into chunks to fit a maximum length.
	- **Returns**: an `std::vector` of `const char*` containing all of the lines split to fit the maximum length.
- `void free_chunks(std::vector<const char*>& chunks)`: since `split()` uses `malloc()`, this function frees the occupied memory.

#### FPS <a name="fps"></a>

- `void cap(Uint64 start, int max, int show = 0, SDL_Renderer* renderer = NULL, TTF_Font* font = NULL)`: caps the frame-per-second rate at a determined `max`. In `main()`, the variable `Uint64 start` keeps track of time, then uses it to cap the fps. If `show > 0` and the rest of the fields are given, a green text displaying the fps rate is shown in the window.

#### Error <a name="error"></a>

Uses the [ANSI escape code sequence](https://en.wikipedia.org/wiki/ANSI_escape_code) to print the text in various colors.
- `void error(const char* s)`: prints a red underlined error message, followed by the `SDL_GetError()` and stops execution.
	- **Returns**: `EXIT_FAILURE`
- `void warning(const char* s)`: prints a yellow warning message.
- `void success(const char* s)`: prints a green message.

#### Colors <a name="colors"></a>

Uses `SDL_Color` to define colors. Every color has members accessible such as `C_WHITE.r`, `C_WHITE.g`, `C_WHITE.b` and `C_WHITE.a`. Alpha is by default set at 255.
