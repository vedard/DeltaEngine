#pragma once

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <random>
#include <sstream>
#include "body.hpp"
#include "world.hpp"
#include "shapes/circle.hpp"
#include "shapes/rectangle.hpp"
#include "shapes/triangle.hpp"

class Window : public sf::RenderWindow, public delta::shapes::AbstractShapeRenderer {
   public:
    Window();
    void run();

   private:
    delta::World world;
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
    void render(delta::shapes::Circle *shape);
    void render(delta::shapes::Shape *shape);
};

