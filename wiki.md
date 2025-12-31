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
		- [Miscellaneous](#misc_src)
			- [Resource Manager](#rm)
		- [2D](#2d)
			- [Image](#image)
			- [Vector2D](#vect2d)
		- [3D](#3d)
			- [Vector3D](#vect3d)
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


#### Miscellaneous <a name="misc_src"></a>

#### Resource Manager <a name="rm"></a>

Each time an image is created, we use the resource manager to efficiently load into memory the appropriate texture by checking an [unordered map](https://en.cppreference.com/w/cpp/container/unordered_map.html), which key is the file path. If found, it returns the texture, otherwise it's created from scratch and then added to the map.
- `SDL_Texture* get_texture(SDL_Renderer* renderer, const char* path)`: returns the texture if found, otherwise creates a new one.
	- **Returns**: appropriate `SDL_Texture*`
- `void remove_texture()`: removes a texture from the map. 

#### 2D <a name="2d"></a>

2D graphics and utilities are here. 

#### Image <a name="image"></a>

`Image` is the class that defines all images rendered onto the window. Every time a image is created, it uses a resource manager to see if it was already loaded into memory. If it's the first instance, it is added, otherwise it's loaded as-is. Each one can be created as such:
- `Image::Image()`: incorrect usage of Image object creation.
	- **Returns**: `EXIT_FAILURE`
- `Image::Image(SDL_Renderer *renderer, const char* image_path, int width, int height)`: instantiates a new Image object onto a given `render`, with the file located in `image_path` (all images are stored into `core/imgs`, a folder then copied into the build directory). By default, `width` and `height` are set to the original image size, but if provided, the image is scaled accordingly.
- `Image::~Image()`: deconstructor, deals with the clean up of memory. Can be called manually or automatically when the program closes.

Then, the following data fields are accessible:

- `int x`: X position.
- `int y`: Y position.
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

#### Vector2D <a name="vect2d"></a>

`Vector2D` is a class that defines bi-dimensional vectors, and their core functionalities. It uses doubles to represent accurately points on the canvas.
- `Vector2D::Vector2D()`: creates a `Vector2D(0.0, 0.0)`
- `Vector2D::Vector2D(double x, double y)`: instantiates a new `Vector2D` object with `(x,y)`. 
	- **Returns**: `Vector2D(x, y)`

Then, the following data fields are accessible:

- `double x`: X position.
- `double y`: Y position.

The following operators:

- `operator+(const Vector2D&, const Vector2D&)`: returns the sum of two vectors.
	- **Returns**: `Vector2D(x1 + x2, y1 + y2)`
- `operator-(const Vector2D&, const Vector2D&)`: returns the subtraction of two vectors.
	- **Returns**: `Vector2D(x1 + (-x2), y1 + (-y2))`
- `operator*(const Vector2D&, const double)`: returns the vector multiplied by a scalar.
	- **Returns**: `Vector2D(x * double, y * double)`
- `operator==(const Vector2D&, const Vector2D&)`
	- **Returns**:	**true** if `x1 == x2` and `y1 == y2`
								else **false**
- `operator!=(const Vector2D&, const Vector2D&)`
	- **Returns**:	**true** if `x1 != x2` or `y1 != y2`
								else **false**
- `operator<(const Vector2D&, const Vector2D&)`
	- **Returns**:	**true** if `x1 < x2` and `y1 < y2`
								else **false**
- `operator>(const Vector2D&, const Vector2D&)`
	- **Returns**:	**true** if `x1 > x2` and `y1 > y2`
								else **false**
- `operator<<(std::ostream&, const Vector2D&)`
	- **Returns**:	a `std::ostream&` object to print out.

And the following methods too:

- `double Vector2D::magnitude()`: returns the magnitude of the vector using the Pythagorean theorem.
	- **Returns**: `double`
- `Vector2D to_vect2d(const Vector3D&)`: transforms a Vector3D object to a Vector2D one.
	- **Returns**: `Vector2D`
- `double dot2d(const Vector2D&, const Vector2D&)`: returns the dot product of two vectors as a scalar.
	- **Returns**: scalar as `double`
- `double angle2d(const Vector2D&, const Vector2D&)`: returns the angle between two vectors in degrees.
	- **Returns**: angle in degrees as `double`

#### 3D <a name="3d"></a>

3D graphics and utilities are here. 

#### Vector3D <a name="vect3d"></a>

`Vector3D` is a class that defines three-dimensional vectors, and their core functionalities. It uses doubles to represent accurately points on the canvas.
- `Vector3D::Vector3D()`: creates a `Vector3D(0.0, 0.0, 0.0)`
- `Vector3D::Vector3D(double x, double y, double z)`: instantiates a new `Vector3D` object with `(x,y,z)`. 
	- **Returns**: `Vector3D(x, y, z)`

Then, the following data fields are accessible:

- `double x`: X position.
- `double y`:Y position.
- `double z`: Z position.

The following operators:

- `operator+(const Vector3D&, const Vector3D&)`: returns the sum of two vectors.
	- **Returns**: `Vector3D(x1 + x2, y1 + y2, z1 + z2)`
- `operator-(const Vector3D&, const Vector3D&)`: returns the subtraction of two vectors.
	- **Returns**: `Vector3D(x1 + (-x2), y1 + (-y2), z1 + (-z2))`
- `operator*(const Vector3D&, const double)`: returns the vector multiplied by a scalar.
	- **Returns**: `Vector3D(x * scalar, y * scalar, z * scalar)`
- `operator==(const Vector3D&, const Vector3D&)`
	- **Returns**:	**true** if `x1 == x2`, `y1 == y2` and `z1 == z2`
								else **false**
- `operator!=(const Vector3D&, const Vector3D&)`
	- **Returns**:	**true** if `x1 != x2`, `y1 != y2` or `z1 != z2`
								else **false**
- `operator<(const Vector3D&, const Vector3D&)`
	- **Returns**:	**true** if `x1 < x2`, `y1 < y2` and `z1 < z2`
								else **false**
- `operator>(const Vector3D&, const Vector3D&)`
	- **Returns**:	**true** if `x1 > x2`, `y1 > y2` and `z1 > z2`
								else **false**
- `operator<<(std::ostream& const Vector3D&)`
	- **Returns**:	a `std::ostream&` object to print out.

And the following methods too:

- `double Vector3D::magnitude()`: returns the magnitude of the vector using the Pythagorean theorem.
	- **Returns**: `double`
- `Vector3D to_vect3d(const Vector2D&)`: transforms a Vector2D object to a Vector3D one.
	- **Returns**: `Vector3D`
- `double dot3d(const Vector3D&, const Vector3D&)`: returns the dot product of two vectors as a scalar.
	- **Returns**: scalar as `double`
- `Vector3D cross3d(const Vector3D&, const Vector3D&)`: returns the cross product of two vectors as vector.
	- **Returns**: cross product as `Vector3D`
- `double angle3d(const Vector3D&, const Vector3D&)`: returns the angle between two vectors in degrees.
	- **Returns**: angle in degrees as `double`

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




