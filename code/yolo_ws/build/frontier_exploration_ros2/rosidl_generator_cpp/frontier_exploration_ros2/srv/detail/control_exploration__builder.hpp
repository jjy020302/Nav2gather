// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from frontier_exploration_ros2:srv/ControlExploration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "frontier_exploration_ros2/srv/control_exploration.hpp"


#ifndef FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__BUILDER_HPP_
#define FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "frontier_exploration_ros2/srv/detail/control_exploration__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace frontier_exploration_ros2
{

namespace srv
{

namespace builder
{

class Init_ControlExploration_Request_quit_after_stop
{
public:
  explicit Init_ControlExploration_Request_quit_after_stop(::frontier_exploration_ros2::srv::ControlExploration_Request & msg)
  : msg_(msg)
  {}
  ::frontier_exploration_ros2::srv::ControlExploration_Request quit_after_stop(::frontier_exploration_ros2::srv::ControlExploration_Request::_quit_after_stop_type arg)
  {
    msg_.quit_after_stop = std::move(arg);
    return std::move(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Request msg_;
};

class Init_ControlExploration_Request_delay_seconds
{
public:
  explicit Init_ControlExploration_Request_delay_seconds(::frontier_exploration_ros2::srv::ControlExploration_Request & msg)
  : msg_(msg)
  {}
  Init_ControlExploration_Request_quit_after_stop delay_seconds(::frontier_exploration_ros2::srv::ControlExploration_Request::_delay_seconds_type arg)
  {
    msg_.delay_seconds = std::move(arg);
    return Init_ControlExploration_Request_quit_after_stop(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Request msg_;
};

class Init_ControlExploration_Request_action
{
public:
  Init_ControlExploration_Request_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlExploration_Request_delay_seconds action(::frontier_exploration_ros2::srv::ControlExploration_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return Init_ControlExploration_Request_delay_seconds(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::frontier_exploration_ros2::srv::ControlExploration_Request>()
{
  return frontier_exploration_ros2::srv::builder::Init_ControlExploration_Request_action();
}

}  // namespace frontier_exploration_ros2


namespace frontier_exploration_ros2
{

namespace srv
{

namespace builder
{

class Init_ControlExploration_Response_message
{
public:
  explicit Init_ControlExploration_Response_message(::frontier_exploration_ros2::srv::ControlExploration_Response & msg)
  : msg_(msg)
  {}
  ::frontier_exploration_ros2::srv::ControlExploration_Response message(::frontier_exploration_ros2::srv::ControlExploration_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Response msg_;
};

class Init_ControlExploration_Response_state
{
public:
  explicit Init_ControlExploration_Response_state(::frontier_exploration_ros2::srv::ControlExploration_Response & msg)
  : msg_(msg)
  {}
  Init_ControlExploration_Response_message state(::frontier_exploration_ros2::srv::ControlExploration_Response::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ControlExploration_Response_message(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Response msg_;
};

class Init_ControlExploration_Response_scheduled
{
public:
  explicit Init_ControlExploration_Response_scheduled(::frontier_exploration_ros2::srv::ControlExploration_Response & msg)
  : msg_(msg)
  {}
  Init_ControlExploration_Response_state scheduled(::frontier_exploration_ros2::srv::ControlExploration_Response::_scheduled_type arg)
  {
    msg_.scheduled = std::move(arg);
    return Init_ControlExploration_Response_state(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Response msg_;
};

class Init_ControlExploration_Response_accepted
{
public:
  Init_ControlExploration_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlExploration_Response_scheduled accepted(::frontier_exploration_ros2::srv::ControlExploration_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ControlExploration_Response_scheduled(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::frontier_exploration_ros2::srv::ControlExploration_Response>()
{
  return frontier_exploration_ros2::srv::builder::Init_ControlExploration_Response_accepted();
}

}  // namespace frontier_exploration_ros2


namespace frontier_exploration_ros2
{

namespace srv
{

namespace builder
{

class Init_ControlExploration_Event_response
{
public:
  explicit Init_ControlExploration_Event_response(::frontier_exploration_ros2::srv::ControlExploration_Event & msg)
  : msg_(msg)
  {}
  ::frontier_exploration_ros2::srv::ControlExploration_Event response(::frontier_exploration_ros2::srv::ControlExploration_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Event msg_;
};

class Init_ControlExploration_Event_request
{
public:
  explicit Init_ControlExploration_Event_request(::frontier_exploration_ros2::srv::ControlExploration_Event & msg)
  : msg_(msg)
  {}
  Init_ControlExploration_Event_response request(::frontier_exploration_ros2::srv::ControlExploration_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_ControlExploration_Event_response(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Event msg_;
};

class Init_ControlExploration_Event_info
{
public:
  Init_ControlExploration_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlExploration_Event_request info(::frontier_exploration_ros2::srv::ControlExploration_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_ControlExploration_Event_request(msg_);
  }

private:
  ::frontier_exploration_ros2::srv::ControlExploration_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::frontier_exploration_ros2::srv::ControlExploration_Event>()
{
  return frontier_exploration_ros2::srv::builder::Init_ControlExploration_Event_info();
}

}  // namespace frontier_exploration_ros2

#endif  // FRONTIER_EXPLORATION_ROS2__SRV__DETAIL__CONTROL_EXPLORATION__BUILDER_HPP_
