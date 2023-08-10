//
//  Brick.hpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#ifndef Brick_hpp
#define Brick_hpp

#include "Object.hpp"
#include <list>
#include <memory>

class Brick : public Object {
typedef std::list<std::unique_ptr<Brick>> Bricks;
public:
    Brick() = delete;
    Brick(const std::string& img_path);
    static void set_bricks(const sf::RenderWindow& window, Bricks& bricks);
    static void draw_bricks(sf::RenderWindow& window, const Bricks& bricks);
    void destroy();
    bool is_destroyed();
private:
    bool exists = true;
};

#endif /* Brick_hpp */
