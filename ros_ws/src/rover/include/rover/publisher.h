#ifndef rover_Publisher_h
#define rover_Publisher_h

#include "rclcpp/rclcpp.hpp"
#include "rover_visualizer/msg/rover_position.hpp"

// internal dependencies
#include "Map/Map.h"
#include "Robot/Robot.h"
#include "Server/Server.h"

extern rclcpp::Node::SharedPtr g_node;
extern rclcpp::Publisher<rover_visualizer::msg::RoverPosition>::SharedPtr
    g_publisher;

class Rover {
 public:
  Rover(Robot robot, Server& monitor, int id, double speed);
  ~Rover();

  void timer_callback();
  void new_goal();
  void operator()();

 private:
  rclcpp::TimerBase::SharedPtr timer_{};

  Robot robot_;
  Server& monitor_;
  int id_;
  double speed_{0.};
};

#endif
