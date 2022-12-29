// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rover_visualizer:msg/RoverPosition.idl
// generated code does not contain a copyright notice

#ifndef ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__TRAITS_HPP_
#define ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rover_visualizer/msg/detail/rover_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace rover_visualizer
{

namespace msg
{

inline void to_flow_style_yaml(
  const RoverPosition & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RoverPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RoverPosition & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace rover_visualizer

namespace rosidl_generator_traits
{

[[deprecated("use rover_visualizer::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rover_visualizer::msg::RoverPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  rover_visualizer::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rover_visualizer::msg::to_yaml() instead")]]
inline std::string to_yaml(const rover_visualizer::msg::RoverPosition & msg)
{
  return rover_visualizer::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rover_visualizer::msg::RoverPosition>()
{
  return "rover_visualizer::msg::RoverPosition";
}

template<>
inline const char * name<rover_visualizer::msg::RoverPosition>()
{
  return "rover_visualizer/msg/RoverPosition";
}

template<>
struct has_fixed_size<rover_visualizer::msg::RoverPosition>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<rover_visualizer::msg::RoverPosition>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<rover_visualizer::msg::RoverPosition>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__TRAITS_HPP_
