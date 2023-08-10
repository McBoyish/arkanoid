//
//  Object.cpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#include "Object.hpp"

Object::Object(const std::string& img_path) {
    texture.loadFromFile(img_path);
    sprite.setTexture(texture);
}

void Object::draw(sf::RenderWindow& window) const { window.draw(sprite); }

const sf::Vector2f& Object::get_pos() const { return sprite.getPosition(); }

void Object::set_pos(float x, float y) { sprite.setPosition(x, y); }

void Object::move(const sf::Vector2f& vector) {
    sprite.setPosition(sprite.getPosition() + vector);
}

float Object::width() const { return sprite.getGlobalBounds().width; }

float Object::height() const { return sprite.getGlobalBounds().height; }

float Object::top() const { return sprite.getGlobalBounds().top; }

float Object::left() const { return sprite.getGlobalBounds().left; }

float Object::bottom() const { return top() + height(); }

float Object::right() const { return left() + width(); }


