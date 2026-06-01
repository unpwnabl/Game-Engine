#include <iostream>
#include <string>

#include "include/gameobj.h"
#include "../../core/misc/include/log.hpp"
#include "../2d/include/image.h"
#include "include/rigidbody.h"

GameObject::GameObject(const char* id, const Vector2D& pos, int width, int height, const Image& image) : name(id), w(width), h(height), img(image) {
	std::string msg = "Created GameObject::" + std::string(name);
	message(msg.c_str());
	position.x = pos.x;
	position.y = pos.y;
	img.set_pos(position);
	img.set_width(w);
	img.set_height(h);
	rb = new Rigidbody(this);
}

GameObject::GameObject(const GameObject& go) : name(go.name), position(go.position), w(go.w), h(go.h), img(go.img) {
	std::string msg = "Copied GameObject::" + std::string(name);
	message(msg.c_str());
}

GameObject::~GameObject() {
	delete rb;
	std::string msg = "Destroyed GameObject::" + std::string(name);
	message(msg.c_str());
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
	img.set_pos(position);
}

int GameObject::get_width() const {
	return w;
}

int GameObject::get_height() const {
	return h;
}

void GameObject::set_width(int n_w) {
	w = n_w;
	img.set_width(w);
}

void GameObject::set_height(int n_h) {
	h = n_h;
	img.set_height(h);
}

Image& GameObject::get_image() {
	return img;
}

const Image& GameObject::get_image() const {
	return img;
}

void GameObject::set_image(const Image& image) {
	img = image;
}

void GameObject::set_image(Image&& image) {
	img = std::move(image);
}

void GameObject::render() const {
	img.render();
}
