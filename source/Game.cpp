//
//  Game.cpp
//  Arkanoid
//
//  Created by Jake Li on 2020-10-12.
//  Copyright © 2020 Jake Li. All rights reserved.
//

#include "Game.hpp"
#include <cmath>
#include <thread>
#include <chrono>

Game::Game(const std::string& title, unsigned width, unsigned height) :
window(sf::VideoMode(width, height), title, sf::Style::Close),
view(sf::Vector2f(width/2, height/2), sf::Vector2f(width + 4.0f, height)),
paddle(resourcePath() + "textures/paddle.png"),
ball(resourcePath() + "textures/ball.png") {
    sound_buffers[static_cast<int>(Sound::WIN)].loadFromFile(resourcePath() + "sounds/win.wav");
    sound_buffers[static_cast<int>(Sound::LOSE)].loadFromFile(resourcePath() + "sounds/lose.wav");
    sound_buffers[static_cast<int>(Sound::START)].loadFromFile(resourcePath() + "sounds/start.wav");
    sound_buffers[static_cast<int>(Sound::HIT)].loadFromFile(resourcePath() + "sounds/hit.wav");
    sounds[static_cast<int>(Sound::WIN)].setBuffer(sound_buffers[static_cast<int>(Sound::WIN)]);
    sounds[static_cast<int>(Sound::LOSE)].setBuffer(sound_buffers[static_cast<int>(Sound::LOSE)]);
    sounds[static_cast<int>(Sound::START)].setBuffer(sound_buffers[static_cast<int>(Sound::START)]);
    sounds[static_cast<int>(Sound::HIT)].setBuffer(sound_buffers[static_cast<int>(Sound::HIT)]);
    window.setView(view);
}

void Game::start() {
    float width = window.getSize().x;
    float height = window.getSize().y;
    paddle.set_pos(width/2 - paddle.width()/2, height - 96.0f);
    ball.set_pos(width/2 - ball.width()/2, height - 96.0f - ball.height());
    ball.reset();
    if (bricks.empty()) {
        for (int i = 0; i < no_of_bricks; ++i) {
            auto ptr = std::make_unique<Brick>(resourcePath() + "textures/brick.png");
            bricks.push_back(std::move(ptr));
        }
        Brick::set_bricks(window, bricks);
    }
    clock.restart();
}

void Game::run() {
    start();
    clock.restart();
    while (window.isOpen()) {
        handleInput();
        dt = clock.restart().asSeconds();
        update();
        draw();
        if (ball.is_invalid()) {
            sounds[static_cast<int>(Sound::LOSE)].play();
            paused = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            start();
        }
        if (bricks.empty()) {
            sounds[static_cast<int>(Sound::WIN)].play();
            paused = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            start();
        }
    }
}

void Game::handleInput() {
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::A) {
                keyboard.A = true;
            } else if (event.key.code == sf::Keyboard::D) {
                keyboard.D = true;
            } else if (event.key.code == sf::Keyboard::Space && paused) {
                sounds[static_cast<int>(Sound::START)].play();
                paused = false;
            }
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::A) {
                keyboard.A = false;
            } else if (event.key.code == sf::Keyboard::D) {
                keyboard.D = false;
            }
            break;
        default:
            break;
        }
    }
}

void Game::update() {
    if (keyboard.A && !keyboard.D) {
        paddle.set_dir(-1);
    } else if (keyboard.D && !keyboard.A) {
        paddle.set_dir(1);
    } else if (keyboard.D && keyboard.A) {
        paddle.set_dir(0);
    } else {
        paddle.set_dir(0);
    }
    paddle.update(dt, window);
    if (!paused) {
        ball.update(dt, window);
        test_collision(paddle, ball);
        for (auto& i : bricks) {
            test_collision(*i, ball);
        }
        auto i = bricks.cbegin();
        while (i != bricks.cend()) {
            if ((*i)->is_destroyed()) {
                i = bricks.erase(i);
            } else {
                ++i;
            }
        }
    } else {
        ball.set_pos(paddle.left() + paddle.width()/2 - ball.width()/2, ball.top());
    }
}

void Game::draw() {
    window.clear();
    Brick::draw_bricks(window, bricks);
    paddle.draw(window);
    ball.draw(window);
    window.display();
}

bool Game::is_intersecting(const Object& obj, Ball& ball) {
    bool intersects = obj.right() > ball.left() && obj.left() < ball.right() &&
                      obj.bottom() > ball.top() && obj.top() < ball.bottom();
    if (intersects) {
        float overlap_top = ball.bottom() - obj.top();
        float overlap_left = ball.right() - obj.left();
        float overlap_bottom = ball.top() - obj.bottom();
        float overlap_right = ball.left() - obj.right();
        bool ball_from_top = (abs(overlap_top) < abs(overlap_bottom));
        bool ball_from_left = (abs(overlap_left) < abs(overlap_right));
        float min_overlap_y = (ball_from_top ? overlap_top : overlap_bottom);
        float min_overlap_x = (ball_from_left ? overlap_left : overlap_right);
        if (abs(min_overlap_x) < abs(min_overlap_y)) {
            float dy = (ball.vel().y/ball.vel().x)*min_overlap_x;
            ball.move(sf::Vector2f(-min_overlap_x, -dy));
        } else {
            float dx = (min_overlap_y/ball.vel().y)*ball.vel().x;
            ball.move(sf::Vector2f(-dx, -min_overlap_y));
        }
    }
    return intersects;
}

void Game::test_collision(const Paddle& paddle, Ball& ball) {
    if (!is_intersecting(paddle, ball)) return;
    float overlap_top = ball.bottom() - paddle.top();
    float overlap_left = ball.right() - paddle.left();
    float overlap_bottom = ball.top() - paddle.bottom();
    float overlap_right = ball.left() - paddle.right();
    bool ball_from_top = (abs(overlap_top) < abs(overlap_bottom));
    bool ball_from_left = (abs(overlap_left) < abs(overlap_right));
    float min_overlap_y = (ball_from_top ? overlap_top : overlap_bottom);
    float min_overlap_x = (ball_from_left ? overlap_left : overlap_right);
    if (abs(min_overlap_y) <= abs(min_overlap_x)) {
        ball.vel().y = (ball_from_top ? -ball.get_speed() : ball.get_speed());
    }
    if (ball.left() + ball.width()/2 < paddle.left() + paddle.width()/2) {
        ball.vel().x = -ball.get_speed();
    } else {
        ball.vel().x = ball.get_speed();
    }
}

void Game::test_collision(Brick& brick, Ball& ball) {
    if (!is_intersecting(brick, ball)) return;
    sounds[static_cast<int>(Sound::HIT)].play();
    brick.destroy();
    float overlap_top = ball.bottom() - brick.top();
    float overlap_left = ball.right() - brick.left();
    float overlap_bottom = ball.top() - brick.bottom();
    float overlap_right = ball.left() - brick.right();
    bool ball_from_top = (abs(overlap_top) < abs(overlap_bottom));
    bool ball_from_left = (abs(overlap_left) < abs(overlap_right));
    float min_overlap_y = (ball_from_top ? overlap_top : overlap_bottom);
    float min_overlap_x = (ball_from_left ? overlap_left : overlap_right);
    if (abs(min_overlap_x) < abs(min_overlap_y)) {
        ball.vel().x = (ball_from_left ? -ball.get_speed() : ball.get_speed());
    } else {
        ball.vel().y = (ball_from_top ? -ball.get_speed() : ball.get_speed());
    }
}
