#include "SimulationManager.hpp"
#include "SFML/Graphics.hpp"
#include "random"


using namespace std;
using namespace sf;

SimulationManager::SimulationManager(size_t boids, int width, int height) {
  std::mt19937 mt(6473);
  std::uniform_int_distribution<int> dist(0,10000); 

  for(int i = 0; i < boids; ++i) {
    CircleShape* shape = new CircleShape(10.f, 3);
    shape->setPosition({ (dist(mt)/10000.f)*width, (dist(mt)/10000.f)*height });
    shapes.push_back(shape);
  }
}

const vector<sf::Shape*> SimulationManager::get_shapes() const {
  return shapes;
};
