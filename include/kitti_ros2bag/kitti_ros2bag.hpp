#pragma once

// ROS header
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <rosbag2_cpp/writer.hpp>
#include <rosbag2_storage/storage_options.hpp>


namespace kitti_ros2bag
{

class KittiROS2BagNode : public rclcpp::Node
{
public:
  KittiROS2BagNode();

private:
  void timer_callback();

  std::unique_ptr<rosbag2_cpp::Writer> writer_;
  rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace kitti_ros2bag
