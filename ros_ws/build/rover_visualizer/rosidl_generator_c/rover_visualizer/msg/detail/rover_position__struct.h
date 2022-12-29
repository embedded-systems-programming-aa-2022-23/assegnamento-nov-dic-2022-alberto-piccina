// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rover_visualizer:msg/RoverPosition.idl
// generated code does not contain a copyright notice

#ifndef ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__STRUCT_H_
#define ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/RoverPosition in the package rover_visualizer.
typedef struct rover_visualizer__msg__RoverPosition
{
  int32_t id;
  geometry_msgs__msg__Point position;
} rover_visualizer__msg__RoverPosition;

// Struct for a sequence of rover_visualizer__msg__RoverPosition.
typedef struct rover_visualizer__msg__RoverPosition__Sequence
{
  rover_visualizer__msg__RoverPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rover_visualizer__msg__RoverPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROVER_VISUALIZER__MSG__DETAIL__ROVER_POSITION__STRUCT_H_
