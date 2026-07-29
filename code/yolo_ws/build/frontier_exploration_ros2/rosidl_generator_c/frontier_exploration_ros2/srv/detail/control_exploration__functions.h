// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from frontier_exploration_ros2:srv/ControlExploration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "frontier_exploration_ros2/srv/control_exploration.h"


#ifndef FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__FUNCTIONS_H_
#define FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "frontier_exploration_ros2/msg/rosidl_generator_c__visibility_control.h"

#include "frontier_exploration_ros2/srv/detail/control_exploration__struct.h"

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_type_hash_t *
frontier_exploration_ros2__srv__ControlExploration__get_type_hash(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeDescription *
frontier_exploration_ros2__srv__ControlExploration__get_type_description(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource *
frontier_exploration_ros2__srv__ControlExploration__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
frontier_exploration_ros2__srv__ControlExploration__get_type_description_sources(
  const rosidl_service_type_support_t * type_support);

/// Initialize srv/ControlExploration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * frontier_exploration_ros2__srv__ControlExploration_Request
 * )) before or use
 * frontier_exploration_ros2__srv__ControlExploration_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Request__init(frontier_exploration_ros2__srv__ControlExploration_Request * msg);

/// Finalize srv/ControlExploration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Request__fini(frontier_exploration_ros2__srv__ControlExploration_Request * msg);

/// Create srv/ControlExploration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * frontier_exploration_ros2__srv__ControlExploration_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
frontier_exploration_ros2__srv__ControlExploration_Request *
frontier_exploration_ros2__srv__ControlExploration_Request__create(void);

/// Destroy srv/ControlExploration message.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Request__destroy(frontier_exploration_ros2__srv__ControlExploration_Request * msg);

/// Check for srv/ControlExploration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Request__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Request * lhs, const frontier_exploration_ros2__srv__ControlExploration_Request * rhs);

/// Copy a srv/ControlExploration message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Request__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Request * input,
  frontier_exploration_ros2__srv__ControlExploration_Request * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_type_hash_t *
frontier_exploration_ros2__srv__ControlExploration_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeDescription *
frontier_exploration_ros2__srv__ControlExploration_Request__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource *
frontier_exploration_ros2__srv__ControlExploration_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/ControlExploration messages.
/**
 * It allocates the memory for the number of elements and calls
 * frontier_exploration_ros2__srv__ControlExploration_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init(frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * array, size_t size);

/// Finalize array of srv/ControlExploration messages.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini(frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * array);

/// Create array of srv/ControlExploration messages.
/**
 * It allocates the memory for the array and calls
 * frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__create(size_t size);

/// Destroy array of srv/ControlExploration messages.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__destroy(frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * array);

/// Check for srv/ControlExploration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * lhs, const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * rhs);

/// Copy an array of srv/ControlExploration messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * input,
  frontier_exploration_ros2__srv__ControlExploration_Request__Sequence * output);

/// Initialize srv/ControlExploration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * frontier_exploration_ros2__srv__ControlExploration_Response
 * )) before or use
 * frontier_exploration_ros2__srv__ControlExploration_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Response__init(frontier_exploration_ros2__srv__ControlExploration_Response * msg);

/// Finalize srv/ControlExploration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Response__fini(frontier_exploration_ros2__srv__ControlExploration_Response * msg);

/// Create srv/ControlExploration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * frontier_exploration_ros2__srv__ControlExploration_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
frontier_exploration_ros2__srv__ControlExploration_Response *
frontier_exploration_ros2__srv__ControlExploration_Response__create(void);

/// Destroy srv/ControlExploration message.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Response__destroy(frontier_exploration_ros2__srv__ControlExploration_Response * msg);

/// Check for srv/ControlExploration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Response__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Response * lhs, const frontier_exploration_ros2__srv__ControlExploration_Response * rhs);

/// Copy a srv/ControlExploration message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Response__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Response * input,
  frontier_exploration_ros2__srv__ControlExploration_Response * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_type_hash_t *
frontier_exploration_ros2__srv__ControlExploration_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeDescription *
frontier_exploration_ros2__srv__ControlExploration_Response__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource *
frontier_exploration_ros2__srv__ControlExploration_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/ControlExploration messages.
/**
 * It allocates the memory for the number of elements and calls
 * frontier_exploration_ros2__srv__ControlExploration_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init(frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * array, size_t size);

/// Finalize array of srv/ControlExploration messages.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini(frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * array);

/// Create array of srv/ControlExploration messages.
/**
 * It allocates the memory for the array and calls
 * frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__create(size_t size);

/// Destroy array of srv/ControlExploration messages.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__destroy(frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * array);

/// Check for srv/ControlExploration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * lhs, const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * rhs);

/// Copy an array of srv/ControlExploration messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * input,
  frontier_exploration_ros2__srv__ControlExploration_Response__Sequence * output);

/// Initialize srv/ControlExploration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * frontier_exploration_ros2__srv__ControlExploration_Event
 * )) before or use
 * frontier_exploration_ros2__srv__ControlExploration_Event__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Event__init(frontier_exploration_ros2__srv__ControlExploration_Event * msg);

/// Finalize srv/ControlExploration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Event__fini(frontier_exploration_ros2__srv__ControlExploration_Event * msg);

/// Create srv/ControlExploration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * frontier_exploration_ros2__srv__ControlExploration_Event__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
frontier_exploration_ros2__srv__ControlExploration_Event *
frontier_exploration_ros2__srv__ControlExploration_Event__create(void);

/// Destroy srv/ControlExploration message.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Event__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Event__destroy(frontier_exploration_ros2__srv__ControlExploration_Event * msg);

/// Check for srv/ControlExploration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Event__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Event * lhs, const frontier_exploration_ros2__srv__ControlExploration_Event * rhs);

/// Copy a srv/ControlExploration message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Event__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Event * input,
  frontier_exploration_ros2__srv__ControlExploration_Event * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_type_hash_t *
frontier_exploration_ros2__srv__ControlExploration_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeDescription *
frontier_exploration_ros2__srv__ControlExploration_Event__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource *
frontier_exploration_ros2__srv__ControlExploration_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/ControlExploration messages.
/**
 * It allocates the memory for the number of elements and calls
 * frontier_exploration_ros2__srv__ControlExploration_Event__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__init(frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * array, size_t size);

/// Finalize array of srv/ControlExploration messages.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Event__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__fini(frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * array);

/// Create array of srv/ControlExploration messages.
/**
 * It allocates the memory for the array and calls
 * frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence *
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__create(size_t size);

/// Destroy array of srv/ControlExploration messages.
/**
 * It calls
 * frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
void
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__destroy(frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * array);

/// Check for srv/ControlExploration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__are_equal(const frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * lhs, const frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * rhs);

/// Copy an array of srv/ControlExploration messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_frontier_exploration_ros2
bool
frontier_exploration_ros2__srv__ControlExploration_Event__Sequence__copy(
  const frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * input,
  frontier_exploration_ros2__srv__ControlExploration_Event__Sequence * output);
#ifdef __cplusplus
}
#endif

#endif  // FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__FUNCTIONS_H_
