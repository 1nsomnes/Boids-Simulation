#include "SFML/Graphics/Shape.hpp"
using namespace std;

class SimulationManager {
  private:
    vector<sf::Shape*> shapes;
  public:
    SimulationManager(size_t, int, int);
    const vector<sf::Shape*> get_shapes() const;
  
};
