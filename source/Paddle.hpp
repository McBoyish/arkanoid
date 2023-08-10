//
//  Paddle.hpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include "Object.hpp"

class Paddle : public Object {
public:
    Paddle() = delete;
    Paddle(const std::string& img_path);
    void update(float dt, const sf::RenderWindow& window);
    void set_dir(int dir);
private:
    const float speed = 400.0f;
    int direction = 0;
};

#endif /* Paddle_hpp */
