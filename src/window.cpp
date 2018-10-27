#include "window.hpp"

Window::Window() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    create(sf::VideoMode(1366, 768), "Vincent", sf::Style::Default, settings);
    this->setFramerateLimit(60);
    font.loadFromFile("./res/Ubuntu-R.ttf");

    this->test_big_ball();
// this->test_cage();
    // this->test_pool();
}

void Window::test_cage() {
    this->world.bodies.push_back(new dt::Body(dt::Vector(1366.f / 2.f, 5.f / 2.f),
                                                 new dt::Rectangle(dt::Vector(1366, 5)), false,
                                                 true));
    this->world.bodies.push_back(new dt::Body(dt::Vector(1366.f / 2.f, 768.f - 5.f / 2.f),
                                                 new dt::Rectangle(dt::Vector(1366, 5)), false,
                                                 true));
    this->world.bodies.push_back(new dt::Body(dt::Vector(5.f / 2.f, 768 / 2.f),
                                                 new dt::Rectangle(dt::Vector(5, 768)), false,
                                                 true));
    this->world.bodies.push_back(new dt::Body(dt::Vector(1366.f - 5.f / 2.f, 768.f / 2.f),
                                                 new dt::Rectangle(dt::Vector(5, 768)), false,
                                                 true));

    this->world.bodies.push_back(
        new dt::Body(dt::Vector(700, 100), new dt::Circle(30.f), true, false));

    std::mt19937 generator(std::random_device{}());
    std::normal_distribution<float> speed_dis(0, 400);
    std::normal_distribution<> position_x(600, 10);
    std::normal_distribution<> position_y(375, 10);
    std::normal_distribution<> radius(80.f, 10.f);
    for (int i = 0; i < 20; i++) {
        dt::Shape* shape = nullptr;

            shape = new dt::Rectangle(dt::Vector(radius(generator), radius(generator)));

        dt::Body* body =
            new dt::Body(dt::Vector(position_x(generator), position_y(generator)), shape, false, false);
        body->velocity = dt::Vector(speed_dis(generator), speed_dis(generator));
        this->world.bodies.push_back(body);
    }
    for(auto&& body : this->world.bodies)
    {
       body->coefficient_restitution =1.f; 
    }
}

void Window::test_big_ball() {
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<> position_x(500.f, 800.f);
    std::uniform_int_distribution<> position_y(-1500, 10);
    std::normal_distribution<> radius(35.f, 4.f);

    // for (size_t i = 0; i < 25; i++) {
    //     this->world.bodies.push_back(new dt::Body(dt::Vector(position_x(generator),
    //     position_y(generator)),
    //                                                 new
    //                                                 dt::Rectangle(dt::Vector(radius(generator),
    //                                                 radius(generator))), true, false));
    // }
    this->world.bodies.push_back(new dt::Body(
        dt::Vector(675.f,760.f), new dt::Rectangle(dt::Vector(1300, 200)), false, true));
    this->world.bodies.push_back(new dt::Body(
        dt::Vector(770.f, 140.f), new dt::Rectangle(dt::Vector(60, 30)), true, false));

    this->world.bodies.back()->velocity = dt::Vector(-300, 0);
    this->world.bodies.back()->angular_velocity = 0.2f;

}

void Window::test_pool() {
    this->world.bodies.push_back(new dt::Body(dt::Vector(700, 50), new dt::Rectangle(dt::Vector(1000, 10.f)), false, true));
    this->world.bodies.push_back(new dt::Body(dt::Vector(440, 10), new dt::Rectangle(dt::Vector(10, 1000.f)), false, true));
    this->world.bodies.push_back(new dt::Body(dt::Vector(750, 10), new dt::Rectangle(dt::Vector(10, 1000.f)), false, true));
    for (int i = 0; i < 5; i++) {
      for (int j = 0 + i; j < 5; j++) {
        dt::Body *c = new dt::Body(
            dt::Vector(500.f + j * 41.f - 20.f * i, 100.f + i * 41.f),
            new dt::Circle(20.f), false, false);
        this->world.bodies.push_back(c);
      }
    }

    dt::Body *b = new dt::Body(dt::Vector(580.f, 900.f), new dt::Circle(20.f), false, false);
    b->velocity = dt::Vector(0.f, -1900.f);

    
    for(auto&& body : this->world.bodies)
    {
       body->coefficient_restitution =1.f; 
    }
    
    this->world.bodies.push_back(b);
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
                    dt::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),
                    new dt::Rectangle(dt::Vector(80, 80)), true, false));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                world.bodies.push_back(new dt::Body(
                    dt::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),
                    new dt::Circle(40), true, false));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                // world.bodies.push_back(new dt::Body(
                //     dt::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),
                //     new dt::Triangle(450), true, false));

                std::mt19937 generator(std::random_device{}());
                std::uniform_real_distribution vertex_position(0.f, 100.f);
                auto *s = new dt::Shape();
                s->points.push_back(dt::Vector(-vertex_position(generator), -vertex_position(generator)));
                s->points.push_back(dt::Vector(vertex_position(generator), -vertex_position(generator)));
                s->points.push_back(dt::Vector(vertex_position(generator), vertex_position(generator)));
                s->points.push_back(dt::Vector(-vertex_position(generator), vertex_position(generator)));
                auto *body = new dt::Body(dt::Vector(sf::Mouse::getPosition(*this).x, sf::Mouse::getPosition(*this).y),s, true, false);
                world.bodies.push_back(body);
                
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        world.bodies.back()->forces += dt::Vector(0, -100);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        world.bodies.back()->forces += dt::Vector(0, 100);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        world.bodies.back()->forces += dt::Vector(-100, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        world.bodies.back()->forces += dt::Vector(100, 0);
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
    image.setRadius(2);
    image.setFillColor(sf::Color::Magenta);
    for (auto&& collision : world.collisions) {
        for (auto&& contact : collision.contacts) {
            image.setPosition(sf::Vector2f(contact.x - 2 , contact.y - 2));
            draw(image);
        }
    }

    draw(text);
    display();
}

void Window::render(dt::Circle* shape) {
    sf::CircleShape image;
    image.setRadius(shape->radius);
    image.setPosition(sf::Vector2f(shape->body->position.x - shape->radius, shape->body->position.y - shape->radius));
    image.setFillColor(sf::Color::Transparent);
    image.setOutlineColor(sf::Color::Cyan);
    image.setOutlineThickness(1);

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
    image.setOutlineThickness(1);
    draw(image);
}