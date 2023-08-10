//
//  Ball.hpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include "Object.hpp"

class Ball : public Object {
public:
    Ball() = delete;
    Ball(const std::string& img_path);
    void update(float dt, const sf::RenderWindow& window);
    void test_window_collision(const sf::RenderWindow& window);
    bool is_invalid();
    sf::Vector2f& vel();
    float get_speed();
    void reset();
private:
    bool invalid = false;
    const float speed = 250.0f;
    sf::Vector2f velocity =  sf::Vector2f(speed, -speed);
};

#endif /* Ball_hpp */
