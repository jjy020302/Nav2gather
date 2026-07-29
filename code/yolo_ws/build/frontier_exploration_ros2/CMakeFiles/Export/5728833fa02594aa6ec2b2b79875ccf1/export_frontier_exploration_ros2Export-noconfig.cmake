#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "frontier_exploration_ros2::frontier_exploration_ros2_core" for configuration ""
set_property(TARGET frontier_exploration_ros2::frontier_exploration_ros2_core APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(frontier_exploration_ros2::frontier_exploration_ros2_core PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfrontier_exploration_ros2_core.so"
  IMPORTED_SONAME_NOCONFIG "libfrontier_exploration_ros2_core.so"
  )

list(APPEND _cmake_import_check_targets frontier_exploration_ros2::frontier_exploration_ros2_core )
list(APPEND _cmake_import_check_files_for_frontier_exploration_ros2::frontier_exploration_ros2_core "${_IMPORT_PREFIX}/lib/libfrontier_exploration_ros2_core.so" )

# Import target "frontier_exploration_ros2::frontier_exploration_ros2_node" for configuration ""
set_property(TARGET frontier_exploration_ros2::frontier_exploration_ros2_node APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(frontier_exploration_ros2::frontier_exploration_ros2_node PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfrontier_exploration_ros2_node.so"
  IMPORTED_SONAME_NOCONFIG "libfrontier_exploration_ros2_node.so"
  )

list(APPEND _cmake_import_check_targets frontier_exploration_ros2::frontier_exploration_ros2_node )
list(APPEND _cmake_import_check_files_for_frontier_exploration_ros2::frontier_exploration_ros2_node "${_IMPORT_PREFIX}/lib/libfrontier_exploration_ros2_node.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
