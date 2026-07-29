// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from frontier_exploration_ros2:srv/ControlExploration.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "frontier_exploration_ros2/srv/detail/control_exploration__rosidl_typesupport_introspection_c.h"
#include "frontier_exploration_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "frontier_exploration_ros2/srv/detail/control_exploration__functions.h"
#include "frontier_exploration_ros2/srv/detail/control_exploration__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  frontier_exploration_ros2__srv__ControlExploration_Request__init(message_memory);
}

void frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_fini_function(void * message_memory)
{
  frontier_exploration_ros2__srv__ControlExploration_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_member_array[3] = {
  {
    "action",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Request, action),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "delay_seconds",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Request, delay_seconds),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "quit_after_stop",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Request, quit_after_stop),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_members = {
  "frontier_exploration_ros2__srv",  // message namespace
  "ControlExploration_Request",  // message name
  3,  // number of fields
  sizeof(frontier_exploration_ros2__srv__ControlExploration_Request),
  false,  // has_any_key_member_
  frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_member_array,  // message members
  frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_type_support_handle = {
  0,
  &frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_members,
  get_message_typesupport_handle_function,
  &frontier_exploration_ros2__srv__ControlExploration_Request__get_type_hash,
  &frontier_exploration_ros2__srv__ControlExploration_Request__get_type_description,
  &frontier_exploration_ros2__srv__ControlExploration_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_frontier_exploration_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Request)() {
  if (!frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_type_support_handle.typesupport_identifier) {
    frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "frontier_exploration_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__functions.h"
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  frontier_exploration_ros2__srv__ControlExploration_Response__init(message_memory);
}

void frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_fini_function(void * message_memory)
{
  frontier_exploration_ros2__srv__ControlExploration_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_member_array[4] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "scheduled",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Response, scheduled),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Response, state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_members = {
  "frontier_exploration_ros2__srv",  // message namespace
  "ControlExploration_Response",  // message name
  4,  // number of fields
  sizeof(frontier_exploration_ros2__srv__ControlExploration_Response),
  false,  // has_any_key_member_
  frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_member_array,  // message members
  frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_type_support_handle = {
  0,
  &frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_members,
  get_message_typesupport_handle_function,
  &frontier_exploration_ros2__srv__ControlExploration_Response__get_type_hash,
  &frontier_exploration_ros2__srv__ControlExploration_Response__get_type_description,
  &frontier_exploration_ros2__srv__ControlExploration_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_frontier_exploration_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Response)() {
  if (!frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_type_support_handle.typesupport_identifier) {
    frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "frontier_exploration_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__functions.h"
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "frontier_exploration_ros2/srv/control_exploration.h"
// Member `request`
// Member `response`
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  frontier_exploration_ros2__srv__ControlExploration_Event__init(message_memory);
}

void frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_fini_function(void * message_memory)
{
  frontier_exploration_ros2__srv__ControlExploration_Event__fini(message_memory);
}

size_t frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__size_function__ControlExploration_Event__request(
  const void * untyped_member)
{
  const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * member =
    (const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_const_function__ControlExploration_Event__request(
  const void * untyped_member, size_t index)
{
  const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * member =
    (const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_function__ControlExploration_Event__request(
  void * untyped_member, size_t index)
{
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * member =
    (frontier_exploration_ros2__srv__ControlExploration_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__fetch_function__ControlExploration_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const frontier_exploration_ros2__srv__ControlExploration_Request * item =
    ((const frontier_exploration_ros2__srv__ControlExploration_Request *)
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_const_function__ControlExploration_Event__request(untyped_member, index));
  frontier_exploration_ros2__srv__ControlExploration_Request * value =
    (frontier_exploration_ros2__srv__ControlExploration_Request *)(untyped_value);
  *value = *item;
}

void frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__assign_function__ControlExploration_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  frontier_exploration_ros2__srv__ControlExploration_Request * item =
    ((frontier_exploration_ros2__srv__ControlExploration_Request *)
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_function__ControlExploration_Event__request(untyped_member, index));
  const frontier_exploration_ros2__srv__ControlExploration_Request * value =
    (const frontier_exploration_ros2__srv__ControlExploration_Request *)(untyped_value);
  *item = *value;
}

bool frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__resize_function__ControlExploration_Event__request(
  void * untyped_member, size_t size)
{
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * member =
    (frontier_exploration_ros2__srv__ControlExploration_Request__Sequence *)(untyped_member);
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini(member);
  return frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init(member, size);
}

size_t frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__size_function__ControlExploration_Event__response(
  const void * untyped_member)
{
  const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * member =
    (const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_const_function__ControlExploration_Event__response(
  const void * untyped_member, size_t index)
{
  const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * member =
    (const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_function__ControlExploration_Event__response(
  void * untyped_member, size_t index)
{
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * member =
    (frontier_exploration_ros2__srv__ControlExploration_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__fetch_function__ControlExploration_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const frontier_exploration_ros2__srv__ControlExploration_Response * item =
    ((const frontier_exploration_ros2__srv__ControlExploration_Response *)
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_const_function__ControlExploration_Event__response(untyped_member, index));
  frontier_exploration_ros2__srv__ControlExploration_Response * value =
    (frontier_exploration_ros2__srv__ControlExploration_Response *)(untyped_value);
  *value = *item;
}

void frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__assign_function__ControlExploration_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  frontier_exploration_ros2__srv__ControlExploration_Response * item =
    ((frontier_exploration_ros2__srv__ControlExploration_Response *)
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_function__ControlExploration_Event__response(untyped_member, index));
  const frontier_exploration_ros2__srv__ControlExploration_Response * value =
    (const frontier_exploration_ros2__srv__ControlExploration_Response *)(untyped_value);
  *item = *value;
}

bool frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__resize_function__ControlExploration_Event__response(
  void * untyped_member, size_t size)
{
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * member =
    (frontier_exploration_ros2__srv__ControlExploration_Response__Sequence *)(untyped_member);
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini(member);
  return frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Event, request),  // bytes offset in struct
    NULL,  // default value
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__size_function__ControlExploration_Event__request,  // size() function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_const_function__ControlExploration_Event__request,  // get_const(index) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_function__ControlExploration_Event__request,  // get(index) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__fetch_function__ControlExploration_Event__request,  // fetch(index, &value) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__assign_function__ControlExploration_Event__request,  // assign(index, value) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__resize_function__ControlExploration_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(frontier_exploration_ros2__srv__ControlExploration_Event, response),  // bytes offset in struct
    NULL,  // default value
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__size_function__ControlExploration_Event__response,  // size() function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_const_function__ControlExploration_Event__response,  // get_const(index) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__get_function__ControlExploration_Event__response,  // get(index) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__fetch_function__ControlExploration_Event__response,  // fetch(index, &value) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__assign_function__ControlExploration_Event__response,  // assign(index, value) function pointer
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__resize_function__ControlExploration_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_members = {
  "frontier_exploration_ros2__srv",  // message namespace
  "ControlExploration_Event",  // message name
  3,  // number of fields
  sizeof(frontier_exploration_ros2__srv__ControlExploration_Event),
  false,  // has_any_key_member_
  frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_member_array,  // message members
  frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_type_support_handle = {
  0,
  &frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_members,
  get_message_typesupport_handle_function,
  &frontier_exploration_ros2__srv__ControlExploration_Event__get_type_hash,
  &frontier_exploration_ros2__srv__ControlExploration_Event__get_type_description,
  &frontier_exploration_ros2__srv__ControlExploration_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_frontier_exploration_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Event)() {
  frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Request)();
  frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Response)();
  if (!frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_type_support_handle.typesupport_identifier) {
    frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "frontier_exploration_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "frontier_exploration_ros2/srv/detail/control_exploration__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_service_members = {
  "frontier_exploration_ros2__srv",  // service namespace
  "ControlExploration",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_Request_message_type_support_handle,
  NULL,  // response message
  // frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_Response_message_type_support_handle
  NULL  // event_message
  // frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_Response_message_type_support_handle
};


static rosidl_service_type_support_t frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_service_type_support_handle = {
  0,
  &frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_service_members,
  get_service_typesupport_handle_function,
  &frontier_exploration_ros2__srv__ControlExploration_Request__rosidl_typesupport_introspection_c__ControlExploration_Request_message_type_support_handle,
  &frontier_exploration_ros2__srv__ControlExploration_Response__rosidl_typesupport_introspection_c__ControlExploration_Response_message_type_support_handle,
  &frontier_exploration_ros2__srv__ControlExploration_Event__rosidl_typesupport_introspection_c__ControlExploration_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    frontier_exploration_ros2,
    srv,
    ControlExploration
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    frontier_exploration_ros2,
    srv,
    ControlExploration
  ),
  &frontier_exploration_ros2__srv__ControlExploration__get_type_hash,
  &frontier_exploration_ros2__srv__ControlExploration__get_type_description,
  &frontier_exploration_ros2__srv__ControlExploration__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_frontier_exploration_ros2
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration)(void) {
  if (!frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_service_type_support_handle.typesupport_identifier) {
    frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, frontier_exploration_ros2, srv, ControlExploration_Event)()->data;
  }

  return &frontier_exploration_ros2__srv__detail__control_exploration__rosidl_typesupport_introspection_c__ControlExploration_service_type_support_handle;
}
