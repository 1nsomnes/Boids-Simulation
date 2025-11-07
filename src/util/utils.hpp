#pragma once

#include "SFML/System/Vector2.hpp"
#include <optional>

namespace utils {

  float distance(sf::Vector2f& p1, sf::Vector2f& p2) ;
  float rotate_direction(float from, float to);
  std::optional<sf::Vector2f> get_relative_distance(sf::Vector2f source_pos, sf::Vector2f to_pos, int width, int height, float distance_threshold);

} // namespace utils
