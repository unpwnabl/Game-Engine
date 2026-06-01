#include "include/font_paths.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <cstring>
#include <cstdlib>

std::string roboto_s = std::string(SDL_GetBasePath()) + "/static/";
std::string roboto_n = roboto_s + "Roboto-Black.ttf";
const char* roboto_path = roboto_n.c_str();
