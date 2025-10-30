#include "SimulationManager.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System/Angle.hpp"
#include "random"


using namespace std;
using namespace sf;

std::mt19937 mt(6473);
std::uniform_int_distribution<int> dist(0,10000); 

float random_percent() {
  return (dist(mt) / 10000.f);
}

SimulationManager::SimulationManager(size_t boids, int width, int height) {
  this->width = width;
  this->height = height;

  for(int i = 0; i < boids; ++i) {
    CircleShape* shape = new CircleShape(8.f, 3);
    shape->setPosition({ random_percent()*width, random_percent()*height });
    shape->setRotation(degrees(360*random_percent()));
    shapes.push_back(shape);
  }
}

void SimulationManager::move_boids(float dist) {
  for(auto boid : shapes) {
    float rad = boid->getRotation().asRadians(); 
    Vector2f direction(cos(rad), sin(rad));

    boid->move(direction * dist);
  }
}

void SimulationManager::reset_edge() {
  for(auto boid : shapes) {
    Vector2f boid_position = boid->getPosition();

    if(boid_position.x < 0) {
      boid_position.x = width;
    } else if(boid_position.x > width) {
      boid_position.x = 0;
    }

    if(boid_position.y < 0) {
      boid_position.y = height;
    } else if(boid_position.y > height) { 
      boid_position.y = 0;
    }

    boid->setPosition(boid_position);
  }
}

const vector<sf::Shape*> SimulationManager::get_shapes() const {
  return shapes;
};
