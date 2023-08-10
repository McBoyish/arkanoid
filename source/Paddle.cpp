//
//  Paddle.cpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#include "Paddle.hpp"

Paddle::Paddle(const std::string& img_path) : Object(img_path) { }

void Paddle::update(float dt, const sf::RenderWindow& window) {
    float ds = direction*dt*speed;
    move(sf::Vector2f(ds, 0.0f));
    if (get_pos().x < 0.0f) {
        set_pos(0.0f, get_pos().y);
    } else if (get_pos().x + width() > window.getSize().x) {
        set_pos(window.getSize().x - width(), get_pos().y);
    }
}

void Paddle::set_dir(int dir) {
    direction = dir;
}
