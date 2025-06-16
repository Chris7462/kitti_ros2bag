#include <chrono>
#include <filesystem>
#include <string>

// local header
#include "kitti_ros2bag/kitti_ros2bag.hpp"

using namespace std::chrono_literals;
namespace fs = std::filesystem;

namespace kitti_ros2bag
{

KittiROS2BagNode::KittiROS2BagNode()
: Node("kitti_ros2bag_node")
{
  // Load all parameters
  std::string base_dir = declare_parameter("base_dir", std::string());
  std::string sequence = declare_parameter("sequence", std::string());
  std::string calib_folder = declare_parameter("calib_folder", std::string());

  // Create a writer
  writer_ = std::make_unique<rosbag2_cpp::Writer>();

  // Specify bag storage options
  rosbag2_storage::StorageOptions storage_options;
  storage_options.uri = sequence + "_bag";  // output bag name
  storage_options.storage_id = "sqlite3";

  // Use default converter
  rosbag2_cpp::ConverterOptions converter_options;
  converter_options.input_serialization_format = "cdr";
  converter_options.output_serialization_format = "cdr";

  // Open bag
  writer_->open(storage_options, converter_options);

  timer_ = create_wall_timer(100ms, std::bind(&KittiROS2BagNode::timer_callback, this));
}

void KittiROS2BagNode::timer_callback()
{
  static int index = 0;

  auto message = std::make_shared<std_msgs::msg::String>();
  message->data = "hello!";
  auto now = get_clock()->now();

  writer_->write(*message, "Chatter", now);

  RCLCPP_INFO(this->get_logger(), "Writing index = %d", index);
  ++index;

  if (index == 10) {
    rclcpp::shutdown();
    return;
  }
}

} // namespace kitti_ros2bag
