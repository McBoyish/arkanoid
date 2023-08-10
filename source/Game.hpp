//
//  Game.hpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include "Keyboard.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"
#include <array>

class Game {
public:
    Game(const std::string& title, unsigned width = 600, unsigned height = 480);
    void start();
    void run();
    void handleInput();
    void update();
    void draw();
    bool is_intersecting(const Object& obj, Ball& ball);
    void test_collision(const Paddle& paddle, Ball& ball);
    void test_collision(Brick& brick, Ball& ball);
    void sleep(int seconds);
private:
    enum class Sound {WIN, LOSE, START, HIT, n};
    std::array<sf::Sound, int(Sound::n)> sounds;
    std::array<sf::SoundBuffer, int(Sound::n)> sound_buffers;
    bool paused = true;
    sf::RenderWindow window;
    sf::View view;
    sf::Event event;
    Keyboard keyboard;
    sf::Clock clock;
    float dt = 0.0f;
    Ball ball;
    Paddle paddle;
    const unsigned rows = 4;
    const unsigned no_of_bricks = rows*10;
    std::list<std::unique_ptr<Brick>> bricks;
};

#endif /* Game_hpp */
