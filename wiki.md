# Game Engine Wiki

## Index

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
		- [Mouse](#mouse)
		- [Event Handler](#eh)
	- [Source](#src)
		- [Miscellaneous](#misc_src)
			- [Resource Manager](#rm)
            - [GameObjects](#go)
            - [Rigidbody](#rb)
		- [2D](#2d)
			- [Image](#image)
			- [Spritesheet](#ss)
			- [Button](#btn)
			- [Vector2D](#vect2d)
		- [3D](#3d)
			- [Vector3D](#vect3d)
	- Audio
	- Images 
- Platform
- [Credits](#credits)

## Functionalities

## UI <a name="ui"></a>

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


## Miscellaneous <a name="misc_src"></a>

#### Resource Manager <a name="rm"></a>

Each time an image is created, we use the resource manager to efficiently load into memory the appropriate texture by checking an [unordered map](https://en.cppreference.com/w/cpp/container/unordered_map.html), which key is the file path. If found, it returns the texture, otherwise it's created from scratch and then added to the map.
- `SDL_Texture* get_texture(SDL_Renderer* renderer, const char* path)`: returns the texture if found, otherwise creates a new one.
	- **Returns**: appropriate `SDL_Texture*`
- `void remove_texture()`: removes a texture from the map.

#### GameObjects <a name="go"></a>

Game objects is an abstract class that defines objects inside the engine.

- `GameObject(const char* name, const Vector2D& pos, int w, int h, SDL_Renderer* renderer, SDL_Color color)`: creates a new GameObject object with a specific `name` at `(pos.x,pos.y)` with `w*h` dimensions. The object has a default color of `C_WHITE` if not provided
- `~GameObject()`: deconstructor, deals with the clean up of memory. Will be called automatically when the program closes.

Then, the following methods are accessible:
- `const char* GameObject::get_name() const`: get the GameObject object name.
	- **Returns**: a `const char*` array.
-  `void GameObject::set_name(const char* n_n)`: set the GameObject object name,
- `Vector2D GameObject::get_pos() const`: get the GameObject object position.
	- **Returns**: a `Vector2D` of the position.
- `void GameObject::set_pos(const Vector2D& n_pos)`: set the GameObject object position using a `Vector2D`.
- `int GameObject::get_width() const`: get the GameObject object width.
	- **Returns**: a `int` of the width.
- `int GameObject::get_height() const`: get the GameObject object height.
	- **Returns**: a `int` of the width.
- `void GameObject::set_width(int n_w)`: set the GameObject object width.
- `void GameObject::set_height(int n_h)`: set the GameObject object height.
- `Image& GameObject::get_image()`: get the image alias.
	- **Returns**: a `Image&` alias.
- `const Image& GameObject::get_image() const`: get the constant image alias, overrides the previous one if needed.
	- **Returns**: a `const Image&` alias.
- `void GameObject::set_image(const Image& image)`: set the GameObject object image using the copy constructor.
- `void GameObject::set_image(Image&& image)`: set the GameObject object image using the move constructor. **More efficent**.
- `GameObject::render()`: renders the `img` into the determined renderer (not the one of the GameObject object, but the one used in the creation of the image).

#### Rigidbody <a name="rb"></a>

The Rigidbody is an abstract class that is responsible for physics simulation inside the game engine. Every [GameObject](#go) has a Rigidbody object attached. Since every Rigidbody is defined as a pointer inside the GameObject, to access its methods it needs the operator `->`

- `Rigidbody::Rigidbody(GameObject* n_go, double n_mass = 0.0, double n_drag = 0.0) noexcept`: creates a new Rigidbody object with a specific `GameObject` with `mass` and `drag`
- `Rigidbody::~Rigidbody()`: deconstructor, deals with the clean up of memory. Will be called automatically when the program closes.

Then, the following methods are accessible:
- `void Rigidbody::set_mass(double n_m)`: set the Rigidbody object mass.
- `void Rigidbody::set_drag(double n_d)`: set the Rigidbody object drag.
- `const double Rigidbody::get_mass() const`: get the Rigidbody object mass.
	- **Returns**: a `const double` of the mass.
- `const double Rigidbody::get_drag() const`: get the Rigidbody object drag.
	- **Returns**: a `const double` of the drag.
- `void Rigidbody::add_force(const Vector2D& f)`: add a force onto the Rigidbody object. Uses $\frac{F.x \times \delta t}{m}$ </br> Always constrained to stay within the screen.
- `void Rigidbody::accelerate(const Vector2D& a)`: accelerate the Rigidbody object. Uses $F.x \times \delta t$ </br> Always constrained to stay within the screen.

- `void Rigidbody::impulse(const Vector2D& i)`: add an impulse onto the Rigidbody object. Uses $\frac{F.x}{m}$ </br> Always constrained to stay within the screen.

- `void Rigidbody::move(const Vector2D& n_pos)`: move the Rigidbody object to a determined `Vector2D` position using LERP and a step of `0.1`. </br> Always constrained to stay within the screen.
- `bool constraint(GameObject* n_go, const Vector2D& max, const Vector2D& min)`: constrain the Rigidbody object into the window of size `(max,min)`.
    - **Returns**: `true` if it's within the constrains, else `false`

## 2D <a name="2d"></a>

2D graphics and utilities are here. 

#### Image <a name="image"></a>

`Image` is the class that defines all images rendered onto the window. Every time a image is created, it uses a resource manager to see if it was already loaded into memory. If it's the first instance, it is added, otherwise it's loaded as-is. Each one can be created as such:
- `Image(SDL_Renderer *renderer, const char* image_path, const Vector2D& pos int width, int height)`: instantiates a new Image object onto a given `render`, with the file located in `image_path` (all images are stored into `core/imgs`, a folder then copied into the build directory) at `(pos.x,pos.y)`. By default, `width` and `height` are set to the original image size, but if provided, the image is scaled accordingly.
- `Image(const Image& img) noexcept`: copy constructor.
- `Image(Image&& img) noexcept`: move constructor.
- `Image::~Image()`: deconstructor, deals with the clean up of memory. Will be called automatically when the program closes.

Then, the following methods are accessible:
- `Vector2D Image::get_pos() const`: get the Image object position.
	- **Returns**: a `Vector2D` of the position.
- `void Image::set_pos(const Vector2D& n_pos)`: set the Image object position using a `Vector2D`.
- `int Image::get_width() const`: get the Image object width.
	- **Returns**: a `int` of the width.
- `int Image::get_height() const`: get the Image object height.
	- **Returns**: a `int` of the width.
- `void Image::set_width(int n_w)`: set the Image object width.
- `void Image::set_height(int n_h)`: set the Image object height.
- `SDL_Color Image::get_color() const`: get the Image object color.
	- **Returns**: a `SDL_Color`
- `void Image::set_color(SDL_Color color)`: changes the image color to the RGBA value of `color`. 
> When this texture is rendered, during the copy operation each source color channel is modulated by the appropriate color value according to the following formula: $src_C = src_C \times (color / 255)$
- `SDL_Renderer* Image::get_renderer() const`: get the Image object renderer.
	- **Returns**: a `SDL_Renderer*`
- `void Image::render(int x_pos, int y_pos)`: renders the image at a given position `(x_pos,y_pos)`. By default, they're set to the origin point, else to the set position.

### Spritesheet <a name="ss"></a>

`Spritesheet` is the class that defines spritesheet usage inside the game engine. When a path is specified, the corresponding image is loaded in memory, and partitioned using the  `x,y,w,h` dimensions provided as such:

- `sprite.x = i * x`
- `sprite.y = (i % frames) * y`
- `sprite.w = w`
- `sprite.h = h`

To render the singular frames, just the index is needed (in a incremental order from the $1^{\text{st}}$ to the $n^{\text{th}}$) to reference it inside the vector that stores them.

- `Spritesheet(SDL_Renderer* renderer, const char* n_path, const Vector2D& n_pos, int n_frames, int n_x, int n_y, int n_w, int n_h, SDL_Color n_color) noexcept`: creates a new Spritesheet object, using the image at `path`, rendering it at `pos`. The image is subdivided into `frames` frames, each having `(x,y)` position and `w*h` size (in the image, not the rendering screen). The  color is by default set to `C_WHITE`
- `~Spritesheet() noexcept`: deconstructor, deals with the clean up of memory. Will be called automatically when the program closes.

Then, the following methods are accessible:
- `Vector2D Spritesheet::get_pos() const`: get the Spritesheet object position.
	- **Returns**: a `Vector2D` of the position.
- `void Spritesheet::set_pos(const Vector2D& n_pos)`: set the Spritesheet object position using a `Vector2D`.
- `int Spritesheet::get_width() const`: get the Spritesheet object width.
	- **Returns**: a `int` of the width.
- `int Spritesheet::get_height() const`: get the Spritesheet object height.
	- **Returns**: a `int` of the width.
- `void Spritesheet::set_width(int n_w)`: set the Spritesheet object width.
- `void Spritesheet::set_height(int n_h)`: set the Spritesheet object height.
- `SDL_Color Spritesheet::get_color() const`: get the Spritesheet object color.
	- **Returns**: a `SDL_Color`
- `void Spritesheet::set_color(SDL_Color color)`: changes the spritesheet color to the RGBA value of `color`. 
> When this texture is rendered, during the copy operation each source color channel is modulated by the appropriate color value according to the following formula: $src_C = src_C \times (color / 255)$
- `void Spritesheet::render(int n_frames)`: renders the image at a given position `(pos.x,pos.x)` using the index `n_frames`

#### Button <a name="btn"></a>

A simple `Button` UI object, derived from [`GameObject`](#gameobj). Each one can be created as such:
- `Button(const char* txt, const Vector2D& pos, int width, int height, const Image& image) noexcept`: creates a button that will display the `txt` at `(pos.x,pos.y)` with size `width*height`, using the `image` as sprite.
- `~Button() noexcept`: deconstructor, deals with the clean up of memory. Will be called automatically when the program closes.

Then, the following methods are accessible:

- `Vector2D Button::get_pos() const`: get the Button object position.
	- **Returns**: a `Vector2D` of the position.
- `void Button::set_pos(const Vector2D& n_pos)`: set the Button object position using a `Vector2D`
- `int Button::get_width() const`: get the Button object width.
	- **Returns**: a `int` of the width.
- `int Button::get_height() const`: get the Button object height.
	- **Returns**: a `int` of the height.
- `void Button::set_width(int n_w)`: set the Button object width.
- `void Button::set_height(int n_h)`: set the Button object height.
- `bool Button::clicked() const`: get the Button object state.
	- **Returns**: `true` if the button is clicked, else `false`
- `void render(TTF_Font* font, int scale = 10, SDL_Color color = C_WHITE) const`: render the `image` and the text using the `font` with size `scale` and color `color`.

#### Vector2D <a name="vect2d"></a>

`Vector2D` is a class that defines bi-dimensional vectors, and their core functionalities. It uses doubles to represent accurately points on the canvas.
- `Vector2D()`: creates a `Vector2D(0.0, 0.0)`
- `Vector2D(double x, double y)`: instantiates a new `Vector2D` object with `(x,y)`. 
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
- `operator<=(const Vector2D&, const Vector2D&)`
	- **Returns**:	**true** if `x1 <= x2` and `y1 <= y2`
								else **false**
- `operator>=(const Vector2D&, const Vector2D&)`
	- **Returns**:	**true** if `x1 >= x2` and `y1 >= y2`
								else **false**
- `operator<<(std::ostream&, const Vector2D&)`
	- **Returns**:	a `std::ostream&` object to print out.

And the following methods too:

- `double Vector2D::magnitude()`: returns the magnitude of the vector using the Pythagorean theorem.
	- **Returns**: `double`
- `Vector2D Vector2D::to_vect2d(const Vector3D&)`: transforms a Vector3D object to a Vector2D one.
	- **Returns**: `Vector2D`
- `double Vector2D::dot2d(const Vector2D&, const Vector2D&)`: returns the dot product of two vectors as a scalar.
	- **Returns**: scalar as `double`
- `double Vector2D::angle2d(const Vector2D&, const Vector2D&)`: returns the angle between two vectors in degrees.
	- **Returns**: angle in degrees as `double`

## 3D <a name="3d"></a>

3D graphics and utilities are here. 

#### Vector3D <a name="vect3d"></a>

`Vector3D` is a class that defines three-dimensional vectors, and their core functionalities. It uses doubles to represent accurately points on the canvas.
- `Vector3D()`: creates a `Vector3D(0.0, 0.0, 0.0)`
- `Vector3D(double x, double y, double z)`: instantiates a new `Vector3D` object with `(x,y,z)`. 
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
- `operator<=(const Vector3D&, const Vector3D&)`
	- **Returns**:	**true** if `x1 <= x2`, `y1 <= y2` and `z1 <= z2`
								else **false**
- `operator>=(const Vector3D&, const Vector3D&)`
	- **Returns**:	**true** if `x1 >= x2`, `y1 >= y2` and `z1 >= z2`
								else **false**
- `operator<<(std::ostream& const Vector3D&)`
	- **Returns**:	a `std::ostream&` object to print out.

And the following methods too:

- `double Vector3D::magnitude()`: returns the magnitude of the vector using the Pythagorean theorem.
	- **Returns**: `double`
- `Vector3D Vector3D::to_vect3d(const Vector2D&)`: transforms a Vector2D object to a Vector3D one.
	- **Returns**: `Vector3D`
- `double Vector3D::dot3d(const Vector3D&, const Vector3D&)`: returns the dot product of two vectors as a scalar.
	- **Returns**: scalar as `double`
- `Vector3D Vector3D::cross3d(const Vector3D&, const Vector3D&)`: returns the cross product of two vectors as vector.
	- **Returns**: cross product as `Vector3D`
- `double Vector3D::angle3d(const Vector3D&, const Vector3D&)`: returns the angle between two vectors in degrees.
	- **Returns**: angle in degrees as `double`

## Misc <a name="misc"></a>

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

#### Mouse <a name="mouse"></a>

Accessible data fields:
- `Vector2D position`: a vector that holds the mouse X and Y positions updated every frame.
- `Vector2D click`: a generic vector that holds the X, Y position in which a mouse button was clicked, updated every frame.
- `Vector2D left_click`: a vector that holds the X, Y position in which the left mouse button was clicked, updated every frame.
- `Vector2D right_click`: a vector that holds the X, Y position in which the right mouse button was clicked, updated every frame.

Methods:

- `Vector2D get_position(SDL_MouseMotionEvent& event)`: gets the mouse X, Y position and stores them in a vector.
	- **Returns**: a `Vector2D` with the mouse's X and Y position.
- `Vector2D clicked(SDL_MouseButtonEvent& event)`: gets the coordinates where a mouse button was pressed, and stores them in a vector.
	- **Returns**: a `Vector2D` with the coordinates.

#### Event Handler <a name="eh"></a>

Every event that SDL captures is processed here.

- `void event_handler(SDL_Window* window, bool& gameloop)`: captures events like mouse or window events to then work with them.

## Credits <a name="credits"></a>
The project and this wiki are updated and maintained by: [Unpwnabl](https://github.com/unpwnabl)
