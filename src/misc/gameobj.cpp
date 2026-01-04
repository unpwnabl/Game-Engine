#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "include/gameobj.h"
#include "../../core/misc/include/log.hpp"
#include "../2d/include/image.h"

GameObject::GameObject(const char* id, int x_pos, int y_pos, int width, int height, SDL_Renderer* renderer, Image& image) : name(id), x(x_pos), y(y_pos), w(width), h(height), go_renderer(renderer), img(image) {
	if (name != "Button") {
		std::cout << "GameObject::" << name << "(" << x << ", " << y << ", " << w << "*" << h << ")" << std::endl;
	}
}

GameObject::~GameObject() {
	img.~Image();
	std::string msg = "Destroyed GameObject::" + std::string(name);
	message(msg.c_str());
}

void GameObject::render() const {
	img.render();
}
