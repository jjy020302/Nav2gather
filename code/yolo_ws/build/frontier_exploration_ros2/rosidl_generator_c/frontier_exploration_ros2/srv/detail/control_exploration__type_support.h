// generated from rosidl_generator_c/resource/idl__type_support.h.em
// with input from frontier_exploration_ros2:srv/ControlExploration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "frontier_exploration_ros2/srv/control_exploration.h"


#ifndef FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__TYPE_SUPPORT_H_
#define FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__TYPE_SUPPORT_H_

#include "rosidl_typesupport_interface/macros.h"

#include "frontier_exploration_ros2/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  frontier_exploration_ros2,
  srv,
  ControlExploration_Request
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  frontier_exploration_ros2,
  srv,
  ControlExploration_Response
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  frontier_exploration_ros2,
  srv,
  ControlExploration_Event
)(void);

#include "rosidl_runtime_c/service_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c,
  frontier_exploration_ros2,
  srv,
  ControlExploration
)(void);

// Forward declare the function to create a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  frontier_exploration_ros2,
  srv,
  ControlExploration
)(
  const rosidl_service_introspection_info_t * info,
  rcutils_allocator_t * allocator,
  const void * request_message,
  const void * response_message);

// Forward declare the function to destroy a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  frontier_exploration_ros2,
  srv,
  ControlExploration
)(
  void * event_msg,
  rcutils_allocator_t * allocator);

#ifdef __cplusplus
}
#endif

#endif  // FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__TYPE_SUPPORT_H_
