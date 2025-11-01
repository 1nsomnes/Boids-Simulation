#pragma once

#include "SFML/System/Vector2.hpp"
#include <optional>

namespace utils {

  float distance(sf::Vector2f& p1, sf::Vector2f& p2) ;
  float rotate_direction(float from, float to);
  bool check_distance(sf::Vector2f , sf::Vector2f , int, int, float);
  std::optional<sf::Vector2f> get_relative_distance(sf::Vector2f , sf::Vector2f , int, int, float);

} // namespace utils
