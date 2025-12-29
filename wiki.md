

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
		- [Log](#log)
		- [Colors](#colors)
	- [Source](#src)
		- [2D](#2d)
			- [Image](#image)
	- Audio
	- Images 
- Platform

## Functionalities

### UI <a name="ui"></a>

Everything concerning the User Interface such as the creation/destruction of windows, renderers, text, etc.. is here. 

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
	- `void generate_text(SDL_Renderer* renderer, const char* s, TTF_Font* font, int x, int y, int scale, SDL_Color fore)`: parent function, takes in an array of characters `s`, creates a `SDL_Surface` from the `renderer` and then creates a `SDL_Texture` in which a rectangle holds the text. If the array of characters `s` is longer than a set maximum length of $max\_len = k * (W_{width} / scale)$, where $k$ is the size of a single character, $W_{width}$ is the width of the window, and $scale$ is the size of the text to be rendered, it is split into chunks and then rendered one by one, using an offset.
- `void close_ttf()`: closes the `SDL_ttf` library and deals with the clean up of memory.

### Source <a name="src"></a>

The source directory has every component tied to the game engine itself.

#### 2D <a name="2d"></a>

2D graphics and utilities are here. 

#### Image <a name="image"></a>

`Image` is the class that defines all images rendered onto the window. Each one can be created as such:
- `Image::Image()`: incorrect usage of Image object creation.
	- **Returns**: `EXIT_FAILURE`
- `Image::Image(SDL_Renderer *renderer, const char* image_path, int width, int height)`: instantiates a new Image object onto a given `render`, with the file located in `image_path` (all images are stored into `core/imgs`, a folder then copied into the build directory). By default, `width` and `height` are set to the original image size, but if provided, the image is scaled accordingly.
- `Image::~Image()`: deconstructor, deals with the clean up of memory. Can be called manually or automatically when the program closes.

Then, the following data fields are accessible:

- `int x`: X position.
- `int y` Y position.
- `int w`: width of image.
- `int h`: height of image.
- `SDL_Point center`: a point indicating the center of the texture.

And the following methods too:

- `void Image::render(int x_pos, int y_pos)`: renders the image at a given position `(x_pos,y_pos)`. By default, they're set to the origin point, else to the set position.
- `void Image::set_color(SDL_Color color)`: changes the image color to the RGBA value of `color`. 
> When this texture is rendered, during the copy operation each source color channel is modulated by the appropriate color value according to the following formula: $src_C = src_C * (color / 255)$
- `void Image::traslate(int nx, int ny)`: traslate the image to a new position at `(nx,ny)`.
- `void Image::rotate(double theta)`: rotates the image by an angle `theta` (in degrees) using `SDL_Point center` as pivot.
- `void Image::scale(double factor)`: scale the image size using a factor.
- `void Image::reflect()`: reflects the image along the Y axis.


### Misc <a name="misc"></a>

The functionalities that aren't specific to one field, and multi-purpose, are here. These include:

#### Split <a name="split"></a>

- `std::vector<const char*> split(const char* s, size_t max_len)`: splits an array of characters `s` into chunks to fit a set maximum length.
	- **Returns**: an `std::vector` of `const char*` containing all of the lines split to fit the maximum length.
- `void free_chunks(std::vector<const char*>& chunks)`: since `split()` uses `malloc()`, this function frees the occupied memory.

#### FPS <a name="fps"></a>

- `void cap(Uint64 start, int max, int show = 0, SDL_Renderer* renderer = NULL, TTF_Font* font = NULL)`: caps the frame-per-second rate at a determined `max`. In `main()`, the variable `Uint64 start` keeps track of time, then is used to cap the FPS. If `show > 0` and the rest of the fields are given, a green text displaying the FPS rate is shown in the window.

#### Log <a name="log"></a>

Uses the [ANSI escape code sequence](https://en.wikipedia.org/wiki/ANSI_escape_code) to print the text in various colors.
- `void sdl_error(const char* s)`: prints a red underlined error message, followed by `SDL_GetError()` and stops execution.
	- **Returns**: `EXIT_FAILURE`
- `void error(const char* s)`: prints a red underlined error message and stops execution.
	- **Returns**: `EXIT_FAILURE`
- `void warning(const char* s)`: prints a yellow warning message.
- `void success(const char* s)`: prints a green message.
- `void message(const char* s)`: prints a grey message.

#### Colors <a name="colors"></a>

Uses `SDL_Color` to define colors. </br>
Every color is RGBA, with  `Uint8 C_WHITE.r`, `Uint8 C_WHITE.g`, `Uint8 C_WHITE.b` and `Uint8 C_WHITE.a`. Alpha is by default set at 255.


