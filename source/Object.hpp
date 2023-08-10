//
//  Object.hpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <SFML/Graphics.hpp>

class Object {
public:
    Object() = delete;
    Object(const std::string& img_path);
    void draw(sf::RenderWindow& window) const;
    const sf::Vector2f& get_pos() const;
    void set_pos(float x, float y);
    void move(const sf::Vector2f& vector);
    float width() const;
    float height() const;
    float top() const;
    float left() const;
    float bottom() const;
    float right() const;
private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif /* Object_hpp */
