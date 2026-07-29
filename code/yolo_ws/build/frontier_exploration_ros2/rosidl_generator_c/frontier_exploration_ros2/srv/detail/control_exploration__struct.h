// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from frontier_exploration_ros2:srv/ControlExploration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "frontier_exploration_ros2/srv/control_exploration.h"


#ifndef FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__STRUCT_H_
#define FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ACTION_START'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__ACTION_START = 1
};

/// Constant 'ACTION_STOP'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__ACTION_STOP = 2
};

/// Constant 'STATE_IDLE'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__STATE_IDLE = 0
};

/// Constant 'STATE_RUNNING'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__STATE_RUNNING = 1
};

/// Constant 'STATE_START_SCHEDULED'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__STATE_START_SCHEDULED = 2
};

/// Constant 'STATE_STOP_SCHEDULED'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__STATE_STOP_SCHEDULED = 3
};

/// Constant 'STATE_STOPPING'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__STATE_STOPPING = 4
};

/// Constant 'STATE_SHUTDOWN_PENDING'.
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Request__STATE_SHUTDOWN_PENDING = 5
};

/// Struct defined in srv/ControlExploration in the package frontier_exploration_ros2.
typedef struct frontier_exploration_ros2__srv__ControlExploration_Request
{
  uint8_t action;
  float delay_seconds;
  bool quit_after_stop;
} frontier_exploration_ros2__srv__ControlExploration_Request;

// Struct for a sequence of frontier_exploration_ros2__srv__ControlExploration_Request.
typedef struct frontier_exploration_ros2__srv__ControlExploration_Request__Sequence
{
  frontier_exploration_ros2__srv__ControlExploration_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} frontier_exploration_ros2__srv__ControlExploration_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ControlExploration in the package frontier_exploration_ros2.
typedef struct frontier_exploration_ros2__srv__ControlExploration_Response
{
  bool accepted;
  bool scheduled;
  uint8_t state;
  rosidl_runtime_c__String message;
} frontier_exploration_ros2__srv__ControlExploration_Response;

// Struct for a sequence of frontier_exploration_ros2__srv__ControlExploration_Response.
typedef struct frontier_exploration_ros2__srv__ControlExploration_Response__Sequence
{
  frontier_exploration_ros2__srv__ControlExploration_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} frontier_exploration_ros2__srv__ControlExploration_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Event__request__MAX_SIZE = 1
};
// response
enum
{
  frontier_exploration_ros2__srv__ControlExploration_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/ControlExploration in the package frontier_exploration_ros2.
typedef struct frontier_exploration_ros2__srv__ControlExploration_Event
{
  service_msgs__msg__ServiceEventInfo info;
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence request;
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence response;
} frontier_exploration_ros2__srv__ControlExploration_Event;

// Struct for a sequence of frontier_exploration_ros2__srv__ControlExploration_Event.
typedef struct frontier_exploration_ros2__srv__ControlExploration_Event__Sequence
{
  frontier_exploration_ros2__srv__ControlExploration_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} frontier_exploration_ros2__srv__ControlExploration_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__STRUCT_H_
