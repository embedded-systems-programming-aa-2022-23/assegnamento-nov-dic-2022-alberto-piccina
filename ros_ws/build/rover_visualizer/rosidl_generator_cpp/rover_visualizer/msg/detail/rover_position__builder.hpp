// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rover_visualizer:msg/RoverPosition.idl
// generated code does not contain a copyright notice

#ifndef ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__BUILDER_HPP_
#define ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rover_visualizer/msg/detail/rover_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rover_visualizer
{

namespace msg
{

namespace builder
{

class Init_RoverPosition_position
{
public:
  explicit Init_RoverPosition_position(::rover_visualizer::msg::RoverPosition & msg)
  : msg_(msg)
  {}
  ::rover_visualizer::msg::RoverPosition position(::rover_visualizer::msg::RoverPosition::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rover_visualizer::msg::RoverPosition msg_;
};

class Init_RoverPosition_id
{
public:
  Init_RoverPosition_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RoverPosition_position id(::rover_visualizer::msg::RoverPosition::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_RoverPosition_position(msg_);
  }

private:
  ::rover_visualizer::msg::RoverPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rover_visualizer::msg::RoverPosition>()
{
  return rover_visualizer::msg::builder::Init_RoverPosition_id();
}

}  // namespace rover_visualizer

#endif  // ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__BUILDER_HPP_
