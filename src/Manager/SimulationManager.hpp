#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
using namespace std;

class SimulationManager {
  private:
    vector<sf::Shape*> shapes;
    int width;
    int height;
  public:
    SimulationManager(size_t, int, int);
    const vector<sf::Shape*> get_shapes() const;
    void move_boids(float);
    void reset_edge();
    void apply_boid_behavior(float);
    void draw_direction_lines(sf::RenderWindow&);
  
};
