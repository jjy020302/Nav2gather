#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to frontier_exploration_ros2__srv__ControlExploration_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ControlExploration_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub action: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub delay_seconds: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub quit_after_stop: bool,

}

impl ControlExploration_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ACTION_START: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ACTION_STOP: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_IDLE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_RUNNING: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_START_SCHEDULED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_STOP_SCHEDULED: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_STOPPING: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_SHUTDOWN_PENDING: u8 = 5;

}


impl Default for ControlExploration_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ControlExploration_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ControlExploration_Request {
  type RmwMsg = super::srv::rmw::ControlExploration_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        action: msg.action,
        delay_seconds: msg.delay_seconds,
        quit_after_stop: msg.quit_after_stop,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      action: msg.action,
      delay_seconds: msg.delay_seconds,
      quit_after_stop: msg.quit_after_stop,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      action: msg.action,
      delay_seconds: msg.delay_seconds,
      quit_after_stop: msg.quit_after_stop,
    }
  }
}


// Corresponds to frontier_exploration_ros2__srv__ControlExploration_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ControlExploration_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub scheduled: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for ControlExploration_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ControlExploration_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ControlExploration_Response {
  type RmwMsg = super::srv::rmw::ControlExploration_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        scheduled: msg.scheduled,
        state: msg.state,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
      scheduled: msg.scheduled,
      state: msg.state,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      scheduled: msg.scheduled,
      state: msg.state,
      message: msg.message.to_string(),
    }
  }
}






#[link(name = "frontier_exploration_ros2__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__frontier_exploration_ros2__srv__ControlExploration() -> *const std::ffi::c_void;
}

// Corresponds to frontier_exploration_ros2__srv__ControlExploration
#[allow(missing_docs, non_camel_case_types)]
pub struct ControlExploration;

impl rosidl_runtime_rs::Service for ControlExploration {
    type Request = ControlExploration_Request;
    type Response = ControlExploration_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__frontier_exploration_ros2__srv__ControlExploration() }
    }
}


