#include "window.hpp"

Window::Window() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 1;
    create(sf::VideoMode(1366, 768), "Vincent", sf::Style::Default, settings);
    this->setFramerateLimit(60);
    font.loadFromFile("./res/Ubuntu-R.ttf");

    auto test = this->getDefaultView();
    test.zoom(1.f / 85.f);
    test.setCenter(8.f,4.5f);
    this->setView(test);

    this->world.bodies.push_back(new dt::Body(dt::Vector(16.f / 2.f, 0.05f / 2.f),
                                                 new dt::Rectangle(dt::Vector(16, 0.05f)), false, true, false));
    this->world.bodies.push_back(new dt::Body(dt::Vector(16.f / 2.f, 9.f - 0.05f / 2.f),
                                                 new dt::Rectangle(dt::Vector(16, 0.05f)), false,
                                                 true, false));
    this->world.bodies.push_back(new dt::Body(dt::Vector(0.05f / 2.f, 9 / 2.f),
                                                 new dt::Rectangle(dt::Vector(0.05f, 9)), false,
                                                 true,false));
    this->world.bodies.push_back(new dt::Body(dt::Vector(16.f - 0.05f / 2.f, 9.f / 2.f),
                                                 new dt::Rectangle(dt::Vector(0.05f, 9)), false,
                                                 true, false));
    dt::Shape* stair = new dt::Shape();
    stair->points.push_back(dt::Vector(3.f, 1.f));
    stair->points.push_back(dt::Vector(-3.f, 1.f));
    stair->points.push_back(dt::Vector(3.f, -1.f));

    this->world.bodies.push_back(new dt::Body(dt::Vector(10.f,8.f), stair, false, true, true));

    this->world.bodies.push_back(
        new dt::Body(dt::Vector(8, 4), new dt::Rectangle(dt::Vector(1.f,1.f)), false, false, true));

        this->world.bodies.back()->linear_damping = 4.f;
}

void Window::run() {
    next_update = update_clock.getElapsedTime().asMilliseconds();
    while (isOpen()) {
        process_input();

        while (update_clock.getElapsedTime().asMilliseconds() > next_update) {
            world.step();
            next_update += update_delay;
        }

        framerate = 1.f / fps_clock.getElapsedTime().asSeconds();
        fps_clock.restart();
        render();
    }
}

void Window::process_input() {
    sf::Event event;
    while (pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            close();
        } else if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                world.bodies.push_back(new dt::Body(
                    dt::Vector(sf::Mouse::getPosition(*this).x / 85.f, sf::Mouse::getPosition(*this).y / 85.f),
                    new dt::Square(1.f), true, false, false));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                world.bodies.push_back(new dt::Body(
                    dt::Vector(sf::Mouse::getPosition(*this).x/ 85.f, sf::Mouse::getPosition(*this).y/ 85.f),
                    new dt::Circle(0.7f), true, false, false));

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                // world.bodies.push_back(new dt::Body(
                //     dt::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),
                //     new dt::Triangle(450), true, false));

                std::mt19937 generator(std::random_device{}());
                std::uniform_real_distribution vertex_position(0.f, 1.f);
                auto *s = new dt::Shape();
                s->points.push_back(dt::Vector(-vertex_position(generator), -vertex_position(generator)));
                s->points.push_back(dt::Vector(vertex_position(generator), -vertex_position(generator)));
                s->points.push_back(dt::Vector(vertex_position(generator), vertex_position(generator)));
                s->points.push_back(dt::Vector(-vertex_position(generator), vertex_position(generator)));
                auto *body = new dt::Body(dt::Vector(sf::Mouse::getPosition(*this).x/ 85.f, sf::Mouse::getPosition(*this).y/ 85.f),s, true, false, false);
                world.bodies.push_back(body);
                
            }
        }
    }

    dt::Vector direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction -= dt::Vector(0, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction += dt::Vector(0, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction -= dt::Vector(1, 0);
        world.bodies.back()->torque -= 10;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction += dt::Vector(1, 0);
        world.bodies.back()->torque += 10;
    }
    world.bodies.back()->forces += direction.normalize() * 20;
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
         
         for(auto&& other : world.bodies)
         {
             dt::Collision c(other, world.bodies.back());
             if (c.Detect() && c.normal.y < 0 ){
                 float angle = atan2f(c.normal.y, c.normal.x);
                 if (angle > -3.f && angle < -0.1415) {
                    world.bodies.back()->forces += dt::Vector(0, -300);
                    other->forces -=  dt::Vector(0, -300);
                    break;
                 }
             }
         }

    }
}

void Window::render() {
    clear(sf::Color(20, 20, 20));

    for (auto&& body : world.bodies) {
        body->shape->render(this);
    }

    sf::CircleShape image;
    image.setRadius(0.02f);
    image.setFillColor(sf::Color::Magenta);
    for (auto&& collision : world.collisions) {
        for (auto&& contact : collision.contacts) {
            image.setPosition(sf::Vector2f(contact.x - 0.02f , contact.y - 0.02f));
            draw(image);
        }
    }

    display();
}

void Window::render(dt::Circle* shape) {
    sf::CircleShape image;
    image.setRadius(shape->radius);
    image.setPosition(sf::Vector2f((shape->body->position.x - shape->radius), (shape->body->position.y - shape->radius)));
    image.setFillColor(sf::Color::Transparent);
    image.setOutlineColor(sf::Color::Cyan);
    image.setOutlineThickness(1.f/ 85.f);

    draw(image);
}

void Window::render(dt::Shape* shape) {
    sf::ConvexShape image;

    image.setPointCount(0);
     for (auto&& vertex : shape->get_vertices()) {
        std::size_t current_size = image.getPointCount();
        image.setPointCount(current_size + 1);
        image.setPoint(current_size, sf::Vector2f(vertex.x, vertex.y));
    }

    image.setFillColor(sf::Color::Transparent);
    image.setOutlineColor(sf::Color::Green);
    image.setOutlineThickness(1.f/ 85.f);
    draw(image);
}