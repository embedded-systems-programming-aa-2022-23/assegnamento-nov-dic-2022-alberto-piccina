// Internal dependencies
#include "rover/publisher.h"

// ROS dependencies
#include "rover_visualizer/msg/rover_position.hpp"

// Standard dependencies
#include <iostream>

using namespace std::chrono_literals;

Rover::Rover(Robot robot, Server& monitor, int id, double speed) 
        : robot_{robot}, monitor_{monitor}, id_(id), speed_(speed)
{
}

Rover::~Rover() {}

void Rover::operator()()
{
  robot_.set_id(id_);
  // std::cout << "Robot's ID setted correctly." << std::endl;
  new_goal();
    // std::cout << "New goal taken correctly." << std::endl;
  timer_ = g_node->create_wall_timer(500ms, std::bind(&Rover::timer_callback, this));
  
  bool loop{true};
  while(loop) {
  }
}

void Rover::timer_callback() {
    // std::cout << "Start timer_callback:" << std::endl;

  if(!robot_.arrived()) {
    robot_mutex.lock();
    robot_.step(5.0);
    robot_mutex.unlock();
  
    auto message{rover_visualizer::msg::RoverPosition()};

    message.id = id_;
    message.position.x = robot_.coordinates().x() + robot_.map().origin().x();
    message.position.y = robot_.coordinates().y() + robot_.map().origin().y();

    g_publisher->publish(message);
  }

  if(robot_.arrived()) {
    std::cout << "Robot " << robot_.id() << " reached (" << robot_.coordinates().x() + robot_.map().origin().x() << ","
            << robot_.coordinates().y() + robot_.map().origin().y() << ")" << std::endl;
    if(!monitor_.goal_queue().empty()) {
      new_goal();
    } else {
      std::cout << "Robot " << robot_.id() << "has no goal to reach." << std::endl;
    }
  }
}

void Rover::new_goal()
{
  robot_.reset();
  robot_.set_goal(monitor_.position_take(robot_.coordinates()));
  std::cout << "Robot " << robot_.id() << " fetched (" << robot_.goal_position().x() + robot_.map().origin().x() << ","
            << robot_.goal_position().y() + robot_.map().origin().y() << ")" << std::endl;
}
