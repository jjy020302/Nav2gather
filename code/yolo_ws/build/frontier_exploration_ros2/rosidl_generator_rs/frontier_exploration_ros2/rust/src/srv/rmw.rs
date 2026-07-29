#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "frontier_exploration_ros2__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__frontier_exploration_ros2__srv__ControlExploration_Request() -> *const std::ffi::c_void;
}

#[link(name = "frontier_exploration_ros2__rosidl_generator_c")]
extern "C" {
    fn frontier_exploration_ros2__srv__ControlExploration_Request__init(msg: *mut ControlExploration_Request) -> bool;
    fn frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ControlExploration_Request>, size: usize) -> bool;
    fn frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ControlExploration_Request>);
    fn frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ControlExploration_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ControlExploration_Request>) -> bool;
}

// Corresponds to frontier_exploration_ros2__srv__ControlExploration_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !frontier_exploration_ros2__srv__ControlExploration_Request__init(&mut msg as *mut _) {
        panic!("Call to frontier_exploration_ros2__srv__ControlExploration_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ControlExploration_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { frontier_exploration_ros2__srv__ControlExploration_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ControlExploration_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ControlExploration_Request where Self: Sized {
  const TYPE_NAME: &'static str = "frontier_exploration_ros2/srv/ControlExploration_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__frontier_exploration_ros2__srv__ControlExploration_Request() }
  }
}


#[link(name = "frontier_exploration_ros2__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__frontier_exploration_ros2__srv__ControlExploration_Response() -> *const std::ffi::c_void;
}

#[link(name = "frontier_exploration_ros2__rosidl_generator_c")]
extern "C" {
    fn frontier_exploration_ros2__srv__ControlExploration_Response__init(msg: *mut ControlExploration_Response) -> bool;
    fn frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ControlExploration_Response>, size: usize) -> bool;
    fn frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ControlExploration_Response>);
    fn frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ControlExploration_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ControlExploration_Response>) -> bool;
}

// Corresponds to frontier_exploration_ros2__srv__ControlExploration_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    pub message: rosidl_runtime_rs::String,

}



impl Default for ControlExploration_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !frontier_exploration_ros2__srv__ControlExploration_Response__init(&mut msg as *mut _) {
        panic!("Call to frontier_exploration_ros2__srv__ControlExploration_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ControlExploration_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { frontier_exploration_ros2__srv__ControlExploration_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ControlExploration_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ControlExploration_Response where Self: Sized {
  const TYPE_NAME: &'static str = "frontier_exploration_ros2/srv/ControlExploration_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__frontier_exploration_ros2__srv__ControlExploration_Response() }
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


