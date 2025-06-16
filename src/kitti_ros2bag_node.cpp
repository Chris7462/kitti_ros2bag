#include "kitti_ros2bag/kitti_ros2bag.hpp"


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<kitti_ros2bag::KittiROS2BagNode>());
  rclcpp::shutdown();

  return 0;
}
