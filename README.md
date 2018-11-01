# Delta
A 2D physics engine

## Example

```c++
#include <iostream>
#include <Delta/delta.hpp>

int main(){

    dt::World world;

    // Create a dynamic body
    dt::Body *ball = new dt::Body(dt::Vector(0.f, 0.f), new dt::Circle(0.5f));

    // Create a static body
    dt::Body *floor = new dt::Body(dt::Vector(0.f, 1.f), new dt::Rectangle(dt::Vector(3.f, 0.2f)), false, true);

    // Add the bodies to the world
    world.bodies.push_back(ball);
    world.bodies.push_back(floor);

    // Check for collision
    while(!dt::Collision(ball, floor).Detect()){

        // Print the position
        std::cout << "Ball position: " << ball->position << std::endl;
        
        // Step 1/60 second into the future
        world.step(); 
    }

    std::cout << "Collision !" << std::endl;

    delete ball;
    delete floor;

    return 0;
}
```
