#pragma once

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <random>
#include <sstream>
#include "Delta/delta.hpp"

class Window : public sf::RenderWindow, public dt::AbstractShapeRenderer {
   public:
    Window();
    void run();

   private:
    dt::World world;
    sf::Clock update_clock;
    sf::Clock fps_clock;
    sf::Font font;
    float framerate = 0.f;
    float next_update = 0.f;
    float update_delay = 1000.f / 60.f;

    void process_input();
    void render();
    void test_big_ball();
    void test_cage();
    void test_pool();
    void render(dt::Circle *shape);
    void render(dt::Shape *shape);
};

