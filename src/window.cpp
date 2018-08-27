#include "window.hpp"

Window::Window() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    create(sf::VideoMode(1366, 768), "Vincent", sf::Style::Default, settings);
    this->setFramerateLimit(60);
    font.loadFromFile("/home/vincent/prog/Dark-Dungeon/res/Ubuntu-Regular.ttf");

    this->test_big_ball();
// this->test_cage();
    // this->test_pool();
}

void Window::test_cage() {
    this->world.bodies.push_back(new delta::Body(delta::math::Vector(1366.f / 2.f, 5.f / 2.f),
                                                 new delta::shapes::Rectangle(delta::math::Vector(1366, 5)), false,
                                                 true));
    this->world.bodies.push_back(new delta::Body(delta::math::Vector(1366.f / 2.f, 768.f - 5.f / 2.f),
                                                 new delta::shapes::Rectangle(delta::math::Vector(1366, 5)), false,
                                                 true));
    this->world.bodies.push_back(new delta::Body(delta::math::Vector(5.f / 2.f, 768 / 2.f),
                                                 new delta::shapes::Rectangle(delta::math::Vector(5, 768)), false,
                                                 true));
    this->world.bodies.push_back(new delta::Body(delta::math::Vector(1366.f - 5.f / 2.f, 768.f / 2.f),
                                                 new delta::shapes::Rectangle(delta::math::Vector(5, 768)), false,
                                                 true));

    this->world.bodies.push_back(
        new delta::Body(delta::math::Vector(700, 100), new delta::shapes::Circle(30.f), true, false));

    // this->world.bodies.push_back(new delta::Body(delta::math::Vector(725, 400),
    //                                      new delta::shapes::Polygon(delta::math::Vector(25, 20)), true, false));
    //                                          this->world.bodies.back()->velocity = delta::math::Vector(0, -300);

    std::mt19937 generator(std::random_device{}());
    std::normal_distribution<float> speed_dis(0, 400);
    std::normal_distribution<> position_x(600, 10);
    std::normal_distribution<> position_y(375, 10);
    std::normal_distribution<> radius(40.f, 10.f);
    for (int i = 0; i < 300; i++) {
        delta::shapes::Shape* shape = nullptr;

        // if (i % 3 == 0)
            shape = new delta::shapes::Rectangle(delta::math::Vector(radius(generator), radius(generator)));
        // else if (i % 2 == 0)
        //     shape = new delta::shapes::Triangle(radius(generator));
        // else
            // shape = new delta::shapes::Circle(radius(generator) / 2);

        delta::Body* body =
            new delta::Body(delta::math::Vector(position_x(generator), position_y(generator)), shape, false, false);
        body->velocity = delta::math::Vector(speed_dis(generator), speed_dis(generator));
        this->world.bodies.push_back(body);
    }
}

void Window::test_big_ball() {
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<> position_x(500.f, 800.f);
    std::uniform_int_distribution<> position_y(-1500, 10);
    std::normal_distribution<> radius(35.f, 4.f);

    // for (size_t i = 0; i < 25; i++) {
    //     this->world.bodies.push_back(new delta::Body(delta::math::Vector(position_x(generator),
    //     position_y(generator)),
    //                                                 new
    //                                                 delta::shapes::Rectangle(delta::math::Vector(radius(generator),
    //                                                 radius(generator))), true, false));
    // }
    this->world.bodies.push_back(new delta::Body(
        delta::math::Vector(770.f, 140.f), new delta::shapes::Rectangle(delta::math::Vector(60, 30)), true, false));

    this->world.bodies.back()->velocity = delta::math::Vector(-300, 0);

    this->world.bodies.push_back(new delta::Body(
        delta::math::Vector(675.f, 700.f), new delta::shapes::Rectangle(delta::math::Vector(1300, 50)), false, true));
}

void Window::test_pool() {
    //     for (int i = 0; i < 5; i++) {
    //         for (int j = 0 + i; j < 5; j++) {
    //             delta::Body* c = new delta::Body(new delta::shapes::Polygon(delta::math::Vector(30.f, 30.f)));
    //             c->is_affected_by_gravity = false;
    //             c->position = delta::math::Vector(500.f + j * 40.f - 20.f * i, 100.f + i * 40.f);
    //             this->world.bodies.push_back(c);
    //         }
    //     }

    //     delta::Body* b = new delta::Body(new delta::shapes::Polygon(delta::math::Vector(30.f, 30.f)));
    //     b->is_affected_by_gravity = false;
    //     b->position = delta::math::Vector(580.f, 700.f);
    //     b->velocity = delta::math::Vector(0.f, -1900.f);
    //     this->world.bodies.push_back(b);
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
                world.bodies.push_back(new delta::Body(
                    delta::math::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),
                    new delta::shapes::Rectangle(delta::math::Vector(30, 30)), true, false));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                world.bodies.push_back(new delta::Body(
                    delta::math::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),
                    new delta::shapes::Circle(15), true, false));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                world.bodies.push_back(new delta::Body(
                    delta::math::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),
                    new delta::shapes::Triangle(450), true, false));
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        world.bodies.back()->forces += delta::math::Vector(0, -100);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        world.bodies.back()->forces += delta::math::Vector(0, 100);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        world.bodies.back()->forces += delta::math::Vector(-100, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        world.bodies.back()->forces += delta::math::Vector(100, 0);
    }
}

void Window::render() {
    clear(sf::Color(20, 20, 20));

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    std::stringstream ss;

    ss << this->framerate << std::endl
       << this->world.bodies.back()->forces << std::endl
       << this->world.bodies.back()->velocity.lenght_squared() << std::endl
       << this->world.bodies.back()->position;
    text.setString(ss.str());

    for (auto&& body : world.bodies) {
        body->shape->render(this);
    }

    sf::CircleShape image;
    image.setRadius(1);
    image.setFillColor(sf::Color::Red);
    for (auto&& collision : world.collisions) {
        for (auto&& contact : collision.contacts) {
            image.setPosition(sf::Vector2f(contact.x, contact.y));
            draw(image);
        }
    }

    draw(text);
    display();
}

void Window::render(delta::shapes::Circle* shape) {
    sf::CircleShape image;
    image.setRadius(shape->radius);
    image.setPosition(sf::Vector2f(shape->body->position.x - shape->radius, shape->body->position.y - shape->radius));
    image.setFillColor(sf::Color::Transparent);
    image.setOutlineColor(sf::Color::Cyan);
    image.setOutlineThickness(1);
    draw(image);
}

void Window::render(delta::shapes::Shape* shape) {
    sf::ConvexShape image;

    image.setPointCount(shape->points.size());
    for (size_t i = 0; i < shape->points.size(); i++) {
        image.setPoint(i, sf::Vector2f(shape->points[i].x, shape->points[i].y));
    }
    image.setRotation(shape->body->angle * 180 / M_PI);
    image.setPosition(sf::Vector2f(shape->body->position.x, shape->body->position.y));
    image.setFillColor(sf::Color::Transparent);
    image.setOutlineColor(sf::Color::Green);
    image.setOutlineThickness(1);
    draw(image);
}