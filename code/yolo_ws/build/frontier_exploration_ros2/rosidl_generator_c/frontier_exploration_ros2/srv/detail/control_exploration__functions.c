// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from frontier_exploration_ros2:srv/ControlExploration.idl
// generated code does not contain a copyright notice
#include "frontier_exploration_ros2/srv/detail/control_exploration__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
frontier_exploration_ros2__srv__ControlExploration_Request__init(frontier_exploration_ros2__srv__ControlExploration_Request * msg)
{
  if (!msg) {
    return false;
  }
  // action
  // delay_seconds
  // quit_after_stop
  return true;
}

void
frontier_exploration_ros2__srv__ControlExploration_Request__fini(frontier_exploration_ros2__srv__ControlExploration_Request * msg)
{
  if (!msg) {
    return;
  }
  // action
  // delay_seconds
  // quit_after_stop
}

bool
frontier_exploration_ros2__srv__ControlExploration_Request__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Request * lhs, const frontier_exploration_ros2__srv__ControlExploration_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // action
  if (lhs->action != rhs->action) {
    return false;
  }
  // delay_seconds
  if (lhs->delay_seconds != rhs->delay_seconds) {
    return false;
  }
  // quit_after_stop
  if (lhs->quit_after_stop != rhs->quit_after_stop) {
    return false;
  }
  return true;
}

bool
frontier_exploration_ros2__srv__ControlExploration_Request__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Request * input,
  frontier_exploration_ros2__srv__ControlExploration_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // action
  output->action = input->action;
  // delay_seconds
  output->delay_seconds = input->delay_seconds;
  // quit_after_stop
  output->quit_after_stop = input->quit_after_stop;
  return true;
}

frontier_exploration_ros2__srv__ControlExploration_Request *
frontier_exploration_ros2__srv__ControlExploration_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Request * msg = (frontier_exploration_ros2__srv__ControlExploration_Request *)allocator.allocate(sizeof(frontier_exploration_ros2__srv__ControlExploration_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(frontier_exploration_ros2__srv__ControlExploration_Request));
  bool success = frontier_exploration_ros2__srv__ControlExploration_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
frontier_exploration_ros2__srv__ControlExploration_Request__destroy(frontier_exploration_ros2__srv__ControlExploration_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    frontier_exploration_ros2__srv__ControlExploration_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init(frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(frontier_exploration_ros2__srv__ControlExploration_Request)) {
      return false;
    }
    data = (frontier_exploration_ros2__srv__ControlExploration_Request *)allocator.zero_allocate(size, sizeof(frontier_exploration_ros2__srv__ControlExploration_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = frontier_exploration_ros2__srv__ControlExploration_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        frontier_exploration_ros2__srv__ControlExploration_Request__fini(&data[i - 1]);
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
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini(frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * array)
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
      frontier_exploration_ros2__srv__ControlExploration_Request__fini(&array->data[i]);
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

frontier_exploration_ros2__srv__ControlExploration_Request__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * array = (frontier_exploration_ros2__srv__ControlExploration_Request__Sequence *)allocator.allocate(sizeof(frontier_exploration_ros2__srv__ControlExploration_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__destroy(frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * lhs, const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!frontier_exploration_ros2__srv__ControlExploration_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * input,
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(frontier_exploration_ros2__srv__ControlExploration_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(frontier_exploration_ros2__srv__ControlExploration_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    frontier_exploration_ros2__srv__ControlExploration_Request * data =
      (frontier_exploration_ros2__srv__ControlExploration_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!frontier_exploration_ros2__srv__ControlExploration_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          frontier_exploration_ros2__srv__ControlExploration_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!frontier_exploration_ros2__srv__ControlExploration_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
frontier_exploration_ros2__srv__ControlExploration_Response__init(frontier_exploration_ros2__srv__ControlExploration_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // scheduled
  // state
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    frontier_exploration_ros2__srv__ControlExploration_Response__fini(msg);
    return false;
  }
  return true;
}

void
frontier_exploration_ros2__srv__ControlExploration_Response__fini(frontier_exploration_ros2__srv__ControlExploration_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // scheduled
  // state
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
frontier_exploration_ros2__srv__ControlExploration_Response__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Response * lhs, const frontier_exploration_ros2__srv__ControlExploration_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // scheduled
  if (lhs->scheduled != rhs->scheduled) {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
frontier_exploration_ros2__srv__ControlExploration_Response__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Response * input,
  frontier_exploration_ros2__srv__ControlExploration_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // scheduled
  output->scheduled = input->scheduled;
  // state
  output->state = input->state;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

frontier_exploration_ros2__srv__ControlExploration_Response *
frontier_exploration_ros2__srv__ControlExploration_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Response * msg = (frontier_exploration_ros2__srv__ControlExploration_Response *)allocator.allocate(sizeof(frontier_exploration_ros2__srv__ControlExploration_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(frontier_exploration_ros2__srv__ControlExploration_Response));
  bool success = frontier_exploration_ros2__srv__ControlExploration_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
frontier_exploration_ros2__srv__ControlExploration_Response__destroy(frontier_exploration_ros2__srv__ControlExploration_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    frontier_exploration_ros2__srv__ControlExploration_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init(frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(frontier_exploration_ros2__srv__ControlExploration_Response)) {
      return false;
    }
    data = (frontier_exploration_ros2__srv__ControlExploration_Response *)allocator.zero_allocate(size, sizeof(frontier_exploration_ros2__srv__ControlExploration_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = frontier_exploration_ros2__srv__ControlExploration_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        frontier_exploration_ros2__srv__ControlExploration_Response__fini(&data[i - 1]);
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
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini(frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * array)
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
      frontier_exploration_ros2__srv__ControlExploration_Response__fini(&array->data[i]);
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

frontier_exploration_ros2__srv__ControlExploration_Response__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * array = (frontier_exploration_ros2__srv__ControlExploration_Response__Sequence *)allocator.allocate(sizeof(frontier_exploration_ros2__srv__ControlExploration_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__destroy(frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * lhs, const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!frontier_exploration_ros2__srv__ControlExploration_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * input,
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(frontier_exploration_ros2__srv__ControlExploration_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(frontier_exploration_ros2__srv__ControlExploration_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    frontier_exploration_ros2__srv__ControlExploration_Response * data =
      (frontier_exploration_ros2__srv__ControlExploration_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!frontier_exploration_ros2__srv__ControlExploration_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          frontier_exploration_ros2__srv__ControlExploration_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!frontier_exploration_ros2__srv__ControlExploration_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__functions.h"

bool
frontier_exploration_ros2__srv__ControlExploration_Event__init(frontier_exploration_ros2__srv__ControlExploration_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    frontier_exploration_ros2__srv__ControlExploration_Event__fini(msg);
    return false;
  }
  // request
  if (!frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init(&msg->request, 0)) {
    frontier_exploration_ros2__srv__ControlExploration_Event__fini(msg);
    return false;
  }
  // response
  if (!frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init(&msg->response, 0)) {
    frontier_exploration_ros2__srv__ControlExploration_Event__fini(msg);
    return false;
  }
  return true;
}

void
frontier_exploration_ros2__srv__ControlExploration_Event__fini(frontier_exploration_ros2__srv__ControlExploration_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini(&msg->request);
  // response
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini(&msg->response);
}

bool
frontier_exploration_ros2__srv__ControlExploration_Event__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Event * lhs, const frontier_exploration_ros2__srv__ControlExploration_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
frontier_exploration_ros2__srv__ControlExploration_Event__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Event * input,
  frontier_exploration_ros2__srv__ControlExploration_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

frontier_exploration_ros2__srv__ControlExploration_Event *
frontier_exploration_ros2__srv__ControlExploration_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Event * msg = (frontier_exploration_ros2__srv__ControlExploration_Event *)allocator.allocate(sizeof(frontier_exploration_ros2__srv__ControlExploration_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(frontier_exploration_ros2__srv__ControlExploration_Event));
  bool success = frontier_exploration_ros2__srv__ControlExploration_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
frontier_exploration_ros2__srv__ControlExploration_Event__destroy(frontier_exploration_ros2__srv__ControlExploration_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    frontier_exploration_ros2__srv__ControlExploration_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__init(frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(frontier_exploration_ros2__srv__ControlExploration_Event)) {
      return false;
    }
    data = (frontier_exploration_ros2__srv__ControlExploration_Event *)allocator.zero_allocate(size, sizeof(frontier_exploration_ros2__srv__ControlExploration_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = frontier_exploration_ros2__srv__ControlExploration_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        frontier_exploration_ros2__srv__ControlExploration_Event__fini(&data[i - 1]);
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
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__fini(frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * array)
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
      frontier_exploration_ros2__srv__ControlExploration_Event__fini(&array->data[i]);
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

frontier_exploration_ros2__srv__ControlExploration_Event__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * array = (frontier_exploration_ros2__srv__ControlExploration_Event__Sequence *)allocator.allocate(sizeof(frontier_exploration_ros2__srv__ControlExploration_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__destroy(frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * lhs, const frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!frontier_exploration_ros2__srv__ControlExploration_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * input,
  frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(frontier_exploration_ros2__srv__ControlExploration_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(frontier_exploration_ros2__srv__ControlExploration_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    frontier_exploration_ros2__srv__ControlExploration_Event * data =
      (frontier_exploration_ros2__srv__ControlExploration_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!frontier_exploration_ros2__srv__ControlExploration_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          frontier_exploration_ros2__srv__ControlExploration_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!frontier_exploration_ros2__srv__ControlExploration_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
