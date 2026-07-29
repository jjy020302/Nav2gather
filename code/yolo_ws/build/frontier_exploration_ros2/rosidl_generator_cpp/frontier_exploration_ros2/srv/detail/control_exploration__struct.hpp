// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from frontier_exploration_ros2:srv/ControlExploration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "frontier_exploration_ros2/srv/control_exploration.hpp"


#ifndef FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__STRUCT_HPP_
#define FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Request __attribute__((deprecated))
#else
# define DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Request __declspec(deprecated)
#endif

namespace frontier_exploration_ros2
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ControlExploration_Request_
{
  using Type = ControlExploration_Request_<ContainerAllocator>;

  explicit ControlExploration_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = 0;
      this->delay_seconds = 0.0f;
      this->quit_after_stop = false;
    }
  }

  explicit ControlExploration_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = 0;
      this->delay_seconds = 0.0f;
      this->quit_after_stop = false;
    }
  }

  // field types and members
  using _action_type =
    uint8_t;
  _action_type action;
  using _delay_seconds_type =
    float;
  _delay_seconds_type delay_seconds;
  using _quit_after_stop_type =
    bool;
  _quit_after_stop_type quit_after_stop;

  // setters for named parameter idiom
  Type & set__action(
    const uint8_t & _arg)
  {
    this->action = _arg;
    return *this;
  }
  Type & set__delay_seconds(
    const float & _arg)
  {
    this->delay_seconds = _arg;
    return *this;
  }
  Type & set__quit_after_stop(
    const bool & _arg)
  {
    this->quit_after_stop = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t ACTION_START =
    1u;
  static constexpr uint8_t ACTION_STOP =
    2u;
  static constexpr uint8_t STATE_IDLE =
    0u;
  static constexpr uint8_t STATE_RUNNING =
    1u;
  static constexpr uint8_t STATE_START_SCHEDULED =
    2u;
  static constexpr uint8_t STATE_STOP_SCHEDULED =
    3u;
  static constexpr uint8_t STATE_STOPPING =
    4u;
  static constexpr uint8_t STATE_SHUTDOWN_PENDING =
    5u;

  // pointer types
  using RawPtr =
    frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Request
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Request
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlExploration_Request_ & other) const
  {
    if (this->action != other.action) {
      return false;
    }
    if (this->delay_seconds != other.delay_seconds) {
      return false;
    }
    if (this->quit_after_stop != other.quit_after_stop) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlExploration_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlExploration_Request_

// alias to use template instance with default allocator
using ControlExploration_Request =
  frontier_exploration_ros2::srv::ControlExploration_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::ACTION_START;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::ACTION_STOP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::STATE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::STATE_RUNNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::STATE_START_SCHEDULED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::STATE_STOP_SCHEDULED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::STATE_STOPPING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ControlExploration_Request_<ContainerAllocator>::STATE_SHUTDOWN_PENDING;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace frontier_exploration_ros2


#ifndef _WIN32
# define DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Response __attribute__((deprecated))
#else
# define DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Response __declspec(deprecated)
#endif

namespace frontier_exploration_ros2
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ControlExploration_Response_
{
  using Type = ControlExploration_Response_<ContainerAllocator>;

  explicit ControlExploration_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
      this->scheduled = false;
      this->state = 0;
      this->message = "";
    }
  }

  explicit ControlExploration_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
      this->scheduled = false;
      this->state = 0;
      this->message = "";
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _scheduled_type =
    bool;
  _scheduled_type scheduled;
  using _state_type =
    uint8_t;
  _state_type state;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__scheduled(
    const bool & _arg)
  {
    this->scheduled = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Response
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Response
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlExploration_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->scheduled != other.scheduled) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlExploration_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlExploration_Response_

// alias to use template instance with default allocator
using ControlExploration_Response =
  frontier_exploration_ros2::srv::ControlExploration_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace frontier_exploration_ros2


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Event __attribute__((deprecated))
#else
# define DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Event __declspec(deprecated)
#endif

namespace frontier_exploration_ros2
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ControlExploration_Event_
{
  using Type = ControlExploration_Event_<ContainerAllocator>;

  explicit ControlExploration_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit ControlExploration_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<frontier_exploration_ros2::srv::ControlExploration_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<frontier_exploration_ros2::srv::ControlExploration_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Event
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__frontier_exploration_ros2__srv__ControlExploration_Event
    std::shared_ptr<frontier_exploration_ros2::srv::ControlExploration_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlExploration_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlExploration_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlExploration_Event_

// alias to use template instance with default allocator
using ControlExploration_Event =
  frontier_exploration_ros2::srv::ControlExploration_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace frontier_exploration_ros2

namespace frontier_exploration_ros2
{

namespace srv
{

struct ControlExploration
{
  using Request = frontier_exploration_ros2::srv::ControlExploration_Request;
  using Response = frontier_exploration_ros2::srv::ControlExploration_Response;
  using Event = frontier_exploration_ros2::srv::ControlExploration_Event;
};

}  // namespace srv

}  // namespace frontier_exploration_ros2

#endif  // FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__STRUCT_HPP_
