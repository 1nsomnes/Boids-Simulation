
#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <iostream>

using namespace std;

namespace utils {

  float distance(sf::Vector2f p1, sf::Vector2f p2) {
    auto diff = p1 - p2;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
  }
  
  // 1 for clock wise -1 for counter clockwise
  float rotate_direction(float from, float to) {
    if(abs(from-to) < 180) return -1.f;
    return 1.f;
  }
} // namespace utils
