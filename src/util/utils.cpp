
#include "utils.hpp";
#include "SFML/System/Vector2.hpp"
#include <cmath>

using namespace std;
using namespace sf;

float utils::distance(sf::Vector2f &p1, sf::Vector2f &p2) {
  auto diff = p1 - p2;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

// 1 for clock wise -1 for counter clockwise
float utils::rotate_direction(float from, float to) {
  // printf("from %f, to %f\n", from, to);
  if (from == 180.f) {
    return 1.f;
  } else if (from < 180.f) {
    auto second_bound = 360 + from - 180;
    if (to >= second_bound || (to >= 0 && to <= from)) {
      return -1.f;
    }
    return 1.f;
  } else {
    auto second_bound = from + 180 - 360.f;
    if (to <= second_bound || to >= from) {
      return 1.f;
    }
    return -1.f;
  }
}

bool utils::check_distance(Vector2f source_pos, Vector2f to_pos, int width, int height, float distance_threshold) {
  auto dist = utils::distance(source_pos, to_pos);
  if(dist < distance_threshold) {
    return true;
  }

  source_pos.x -= width;
  dist = utils::distance(source_pos, to_pos);
  if(dist < distance_threshold) {
    return true;
  }

  source_pos.x += 2*width;
  dist = utils::distance(source_pos, to_pos);
  if(dist < distance_threshold) {
    return true;
  }

  source_pos.x -= width;
  source_pos.y += height;
  dist = utils::distance(source_pos, to_pos);
  if(dist< distance_threshold) {
    return true;
  }

  source_pos.y -= 2*height;
  dist = utils::distance(source_pos, to_pos);
  if(dist < distance_threshold) {
    return true;
  }

  return false;
}
