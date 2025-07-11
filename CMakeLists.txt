cmake_minimum_required(VERSION 3.8)
project(kitti_ros2bag)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(rosbag2_storage REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(kitti_ros2bag_node
  src/kitti_ros2bag_node.cpp
  src/kitti_ros2bag.cpp)

target_include_directories(kitti_ros2bag_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_target_dependencies(kitti_ros2bag_node PUBLIC
  rclcpp
  rosbag2_cpp
  rosbag2_storage
  std_msgs)

# target_link_libraries(kitti_ros2bag_node PUBLIC
#   opencv_imgcodecs
#   ${PCL_LIBRARIES})

target_compile_features(kitti_ros2bag_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS kitti_ros2bag_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY params
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
