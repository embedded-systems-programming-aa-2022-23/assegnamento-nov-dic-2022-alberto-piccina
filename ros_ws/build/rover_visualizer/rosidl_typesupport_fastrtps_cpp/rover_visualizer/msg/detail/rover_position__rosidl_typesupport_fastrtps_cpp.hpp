// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from rover_visualizer:msg/RoverPosition.idl
// generated code does not contain a copyright notice

#ifndef ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "rover_visualizer/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "rover_visualizer/msg/detail/rover_position__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace rover_visualizer
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rover_visualizer
cdr_serialize(
  const rover_visualizer::msg::RoverPosition & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rover_visualizer
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  rover_visualizer::msg::RoverPosition & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rover_visualizer
get_serialized_size(
  const rover_visualizer::msg::RoverPosition & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rover_visualizer
max_serialized_size_RoverPosition(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace rover_visualizer

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_rover_visualizer
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rover_visualizer, msg, RoverPosition)();

#ifdef __cplusplus
}
#endif

#endif  // ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
