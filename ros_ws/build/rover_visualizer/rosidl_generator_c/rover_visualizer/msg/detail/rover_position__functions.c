// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rover_visualizer:msg/RoverPosition.idl
// generated code does not contain a copyright notice
#include "rover_visualizer/msg/detail/rover_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
rover_visualizer__msg__RoverPosition__init(rover_visualizer__msg__RoverPosition * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    rover_visualizer__msg__RoverPosition__fini(msg);
    return false;
  }
  return true;
}

void
rover_visualizer__msg__RoverPosition__fini(rover_visualizer__msg__RoverPosition * msg)
{
  if (!msg) {
    return;
  }
  // id
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
}

bool
rover_visualizer__msg__RoverPosition__are_equal(const rover_visualizer__msg__RoverPosition * lhs, const rover_visualizer__msg__RoverPosition * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  return true;
}

bool
rover_visualizer__msg__RoverPosition__copy(
  const rover_visualizer__msg__RoverPosition * input,
  rover_visualizer__msg__RoverPosition * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  return true;
}

rover_visualizer__msg__RoverPosition *
rover_visualizer__msg__RoverPosition__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rover_visualizer__msg__RoverPosition * msg = (rover_visualizer__msg__RoverPosition *)allocator.allocate(sizeof(rover_visualizer__msg__RoverPosition), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rover_visualizer__msg__RoverPosition));
  bool success = rover_visualizer__msg__RoverPosition__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rover_visualizer__msg__RoverPosition__destroy(rover_visualizer__msg__RoverPosition * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rover_visualizer__msg__RoverPosition__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rover_visualizer__msg__RoverPosition__Sequence__init(rover_visualizer__msg__RoverPosition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rover_visualizer__msg__RoverPosition * data = NULL;

  if (size) {
    data = (rover_visualizer__msg__RoverPosition *)allocator.zero_allocate(size, sizeof(rover_visualizer__msg__RoverPosition), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rover_visualizer__msg__RoverPosition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rover_visualizer__msg__RoverPosition__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rover_visualizer__msg__RoverPosition__Sequence__fini(rover_visualizer__msg__RoverPosition__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rover_visualizer__msg__RoverPosition__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rover_visualizer__msg__RoverPosition__Sequence *
rover_visualizer__msg__RoverPosition__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rover_visualizer__msg__RoverPosition__Sequence * array = (rover_visualizer__msg__RoverPosition__Sequence *)allocator.allocate(sizeof(rover_visualizer__msg__RoverPosition__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rover_visualizer__msg__RoverPosition__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rover_visualizer__msg__RoverPosition__Sequence__destroy(rover_visualizer__msg__RoverPosition__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rover_visualizer__msg__RoverPosition__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rover_visualizer__msg__RoverPosition__Sequence__are_equal(const rover_visualizer__msg__RoverPosition__Sequence * lhs, const rover_visualizer__msg__RoverPosition__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rover_visualizer__msg__RoverPosition__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rover_visualizer__msg__RoverPosition__Sequence__copy(
  const rover_visualizer__msg__RoverPosition__Sequence * input,
  rover_visualizer__msg__RoverPosition__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rover_visualizer__msg__RoverPosition);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rover_visualizer__msg__RoverPosition * data =
      (rover_visualizer__msg__RoverPosition *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rover_visualizer__msg__RoverPosition__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rover_visualizer__msg__RoverPosition__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rover_visualizer__msg__RoverPosition__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
