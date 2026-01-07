#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "include/gameobj.h"
#include "../../core/misc/include/log.hpp"
#include "../2d/include/image.h"

GameObject::GameObject(const char* id, Vector2D pos, int width, int height, SDL_Renderer* renderer, Image& image) : name(id), w(width), h(height), go_renderer(renderer), img(image) {
	std::string msg = "Created GameObject::" + std::string(name);
	message(msg.c_str());
	position.x = pos.x;
	position.y = pos.y;
}

GameObject::GameObject(const GameObject& go) : go_renderer(go.go_renderer), name(go.name), position(go.position), w(go.w), h(go.h), img(go.img) {
	std::string msg = "Copied GameObject::" + std::string(name);
	message(msg.c_str());
}

GameObject::~GameObject() {
	go_renderer = NULL;
	position.~Vector2D();
	std::string msg = "Destroyed GameObject::" + std::string(name);
	name = "";
	message(msg.c_str());
}

void GameObject::set_renderer(SDL_Renderer* renderer) {
	go_renderer = renderer;
}

const char* GameObject::get_name() const {
	return name;
}

void GameObject::set_name(const char* n_n) {
	name = n_n;
}

Vector2D GameObject::get_pos() const {
	return position;
}

void GameObject::set_pos(const Vector2D& n_pos) {
	position = n_pos;
}

int GameObject::get_width() const {
	return w;
}

int GameObject::get_height() const {
	return h;
}

void GameObject::set_width(int n_w) {
	w = n_w;
}

void GameObject::set_height(int n_h) {
	h = n_h;
}

Image GameObject::get_image() const {
	return img;
}

void GameObject::set_image(const Image& image) {
	img = image;
}

void GameObject::render() const {
	img.render();
}
