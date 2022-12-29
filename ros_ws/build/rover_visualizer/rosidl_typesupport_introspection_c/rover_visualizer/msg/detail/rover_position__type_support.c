// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rover_visualizer:msg/RoverPosition.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rover_visualizer/msg/detail/rover_position__rosidl_typesupport_introspection_c.h"
#include "rover_visualizer/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rover_visualizer/msg/detail/rover_position__functions.h"
#include "rover_visualizer/msg/detail/rover_position__struct.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/point.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rover_visualizer__msg__RoverPosition__init(message_memory);
}

void rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_fini_function(void * message_memory)
{
  rover_visualizer__msg__RoverPosition__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_member_array[2] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_visualizer__msg__RoverPosition, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_visualizer__msg__RoverPosition, position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_members = {
  "rover_visualizer__msg",  // message namespace
  "RoverPosition",  // message name
  2,  // number of fields
  sizeof(rover_visualizer__msg__RoverPosition),
  rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_member_array,  // message members
  rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_init_function,  // function to initialize message memory (memory has to be allocated)
  rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_type_support_handle = {
  0,
  &rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rover_visualizer
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rover_visualizer, msg, RoverPosition)() {
  rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_type_support_handle.typesupport_identifier) {
    rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rover_visualizer__msg__RoverPosition__rosidl_typesupport_introspection_c__RoverPosition_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
