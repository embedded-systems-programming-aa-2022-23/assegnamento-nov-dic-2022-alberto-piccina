// Internal dependencies
#include "rover/publisher.h"

// ROS dependencies
#include "rover_visualizer/msg/rover_position.hpp"

// Standard dependencies
#include <iostream>

using namespace std::chrono_literals;

Rover::Rover(int id, double speed) : id_(id), speed_(speed) {
  timer_ =
      g_node->create_wall_timer(500ms, std::bind(&Rover::timer_callback, this));
}

Rover::~Rover() {}

void Rover::timer_callback() {
  auto message{rover_visualizer::msg::RoverPosition()};

  x_pos_ += speed_;
  y_pos_ += speed_;

  message.id = id_;
  message.position.x = x_pos_;
  message.position.y = y_pos_;

  g_publisher->publish(message);
}

void Rover::setY_pos(double y_pos) { y_pos_ = y_pos; }

void Rover::setX_pos(double x_pos) { x_pos_ = x_pos; }
