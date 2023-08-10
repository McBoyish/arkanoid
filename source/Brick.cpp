//
//  Brick.cpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#include "Brick.hpp"

Brick::Brick(const std::string& img_path) : Object(img_path) { }

void Brick::set_bricks(const sf::RenderWindow& window, Bricks& bricks) {
    auto brick = bricks.begin();
    float width = (*brick)->width();
    float height = (*brick)->height();
    unsigned columns = 0;
    unsigned rows = 0;
    while (brick != bricks.end()) {
        (*brick)->set_pos(columns*width, rows*height);
        ++columns;
        ++brick;
        if (columns == window.getSize().x/width) {
            ++rows;
            columns = 0;
        }
    }
}

void Brick::draw_bricks(sf::RenderWindow& window, const Bricks& bricks) {
    for (const auto& i : bricks) {
        i->draw(window);
    }
}

void Brick::destroy() {
    exists = false;
}

bool Brick::is_destroyed() {
    return !exists;
}
