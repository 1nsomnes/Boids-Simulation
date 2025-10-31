#include "SimulationManager.hpp"
#include "../util/utils.cpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Angle.hpp"
#include "SFML/System/Vector2.hpp"
#include "random"
#include <iostream>

using namespace std;
using namespace sf;

std::mt19937 mt(6473);
std::uniform_int_distribution<int> dist(0, 10000);

const float steer_strength = 70.f;

float random_percent() { return (dist(mt) / 10000.f); }

SimulationManager::SimulationManager(size_t boids, int width, int height) {
  this->width = width;
  this->height = height;

  for (int i = 0; i < boids; ++i) {
    ConvexShape *shape = new ConvexShape();

    shape->setPointCount(3);
    shape->setPoint(0, {-8.f, -4.f});
    shape->setPoint(1, {-8.f, 4.f});
    shape->setPoint(2, {8.f, 0.f});

    shape->setPosition({random_percent() * width, random_percent() * height});
    shape->setRotation(degrees(360 * random_percent()));
    shapes.push_back(shape);
  }
}

void SimulationManager::move_boids(float dist) {
  for (auto boid : shapes) {
    float rad = boid->getRotation().asRadians();
    Vector2f direction(cos(rad), sin(rad));

    boid->move(direction * dist);
  }
}

void SimulationManager::reset_edge() {
  for (auto boid : shapes) {
    Vector2f boid_position = boid->getPosition();

    if (boid_position.x < 0) {
      boid_position.x = width;
    } else if (boid_position.x > width) {
      boid_position.x = 0;
    }

    if (boid_position.y < 0) {
      boid_position.y = height;
    } else if (boid_position.y > height) {
      boid_position.y = 0;
    }

    boid->setPosition(boid_position);
  }
}

float calculate_separation(const Shape *source,
                           const vector<Shape *> within_radius) {
  if(within_radius.size() == 0) return 0.f;

  Vector2f com = {0.f, 0.f};
  for(int i = 0; i < within_radius.size(); ++i) {
    com += within_radius[i]->getPosition() - source->getPosition();
  }

  int num_of_points = within_radius.size();
  com.x /= -num_of_points;
  com.y /= -num_of_points;

  auto com_angle = com.angle().asDegrees();
  if (com_angle < 0) com_angle += 360;
  float direction = utils::rotate_direction(source->getRotation().asDegrees(), com_angle);
  
  return steer_strength * direction;
}

float calculate_alignment(const Shape *source,
                          const vector<Shape *> within_radius) {
  if(within_radius.size() == 0) return 0.f;

  float avg_rotation = source->getRotation().asDegrees();
  for(int i = 0; i < within_radius.size(); ++i) {
    avg_rotation += within_radius[i]->getRotation().asDegrees();
  }

  int num_of_points = within_radius.size()+1;
  avg_rotation /= num_of_points;

  float direction = utils::rotate_direction(source->getRotation().asDegrees(), avg_rotation);
  
  return steer_strength * direction;

}

float calculate_cohesion(const Shape *source,
                         const vector<Shape *> within_radius) {
  if(within_radius.size() == 0) return 0.f;

  Vector2f com = source->getPosition();
  for(int i = 0; i < within_radius.size(); ++i) {
    com += within_radius[i]->getPosition();
  }

  int num_of_points = within_radius.size()+1;
  com.x /= num_of_points;
  com.y /= num_of_points;

  com = com - source->getPosition();

  auto com_angle = com.angle().asDegrees();
  if (com_angle < 0) com_angle += 360;
  float direction = utils::rotate_direction(source->getRotation().asDegrees(), com_angle);
  
  return steer_strength * direction;
}

void SimulationManager::apply_boid_behavior(float deltaTime) {
  for (int i = 0; i < shapes.size(); ++i) {
    vector<Shape *> within_radius;

    for (int j = 0; j < shapes.size(); ++j) {
      if (i != j) {
        auto dist =
            utils::distance(shapes[i]->getPosition(), shapes[j]->getPosition());
        if (dist < 300) {
          within_radius.push_back(shapes[j]);
        }
      }
    }
    const float weights[3] = {0.2f, 0.4f, 0.2f};
    auto applied_rotation = weights[0] * calculate_separation(shapes[i], within_radius) +
                            weights[1] * calculate_alignment(shapes[i], within_radius) +
                            weights[2] * calculate_cohesion(shapes[i], within_radius);
    applied_rotation *= deltaTime;
    

    shapes[i]->rotate(degrees(applied_rotation));
  }
}

void SimulationManager::draw_direction_lines(RenderWindow& window) {
  vector<RectangleShape> lines;

  for( auto shape: shapes) {
    RectangleShape line({50.f, 0.8f});
    line.setRotation(shape->getRotation());
    line.setPosition(shape->getPosition());
    lines.push_back(line);
  }

  for( auto line: lines) window.draw(line);
}

const vector<sf::Shape *> SimulationManager::get_shapes() const {
  return shapes;
};
