//
//  Ball.cpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#include "Ball.hpp"

Ball::Ball(const std::string& img_path) : Object(img_path) { }

void Ball::update(float dt, const sf::RenderWindow& window) {
    float dx = dt*velocity.x;
    float dy = dt*velocity.y;
    move(sf::Vector2f(dx, dy));
    test_window_collision(window);
}

void Ball::test_window_collision(const sf::RenderWindow& window) {
    if (get_pos().x < 0.0f) {
        set_pos(0.0f, get_pos().y);
        velocity.x = speed;
    } else if (get_pos().x + width() > window.getSize().x) {
        set_pos(window.getSize().x - width(), get_pos().y);
        velocity.x = -speed;
    }
    if (get_pos().y < 0.0f) {
        set_pos(get_pos().x, 0.0f);
        velocity.y = speed;
    } else if (get_pos().y + height() > window.getSize().y) {
        set_pos(get_pos().x, window.getSize().y - height());
        invalid = true;
    }
}

bool Ball::is_invalid() {
    return invalid;
}

sf::Vector2f& Ball::vel() {
    return velocity;
}

float Ball::get_speed() {
    return speed;
}

void Ball::reset() {
    invalid = false;
    velocity.x = speed;
    velocity.y = -speed;
}
