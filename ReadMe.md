# KITTI ROS2 Bag
As there was no existing package available to directly convert KITTI raw data into a ROS2 bag, I created this repository to fill that gap.

Note: This repository currently supports only the conversion of KITTI raw data into ROS2 bag format. Contributions to extend its functionality are welcome.

## Getting Started
### 1. Download KITTI Raw Data
Download and unzip the raw KITTI dataset from the [official website](https://www.cvlibs.net/datasets/kitti/raw_data.php)

### 2. Clone the Repository
Clone this repository and [kitti_dataloader](https://github.com/Chris7462/kitti_dataloader.git) into your ROS2 workspace's `src` folder.
```bash
cd ~/ros2_ws/src
git clone https://github.com/Chris7462/kitti_ros2bag.git
git clone https://github.com/Chris7462/kitti_dataloader.git
```
Note: kitti_dataloader is a C++ library that handles parsing and loading of the KITTI dataset. It is a required dependency for kitti_ros2bag.
### 3. Configure Parameters
Edit the `params/kitti_ros2bag.yaml` file:
```yaml
base_dir: "/data/kitti/raw/2011_09_29"  # Absolute path to base directory
sequence: "2011_09_29_drive_0071_sync"  # The specific drive to convert
calib_folder: ""                        # (Optional) Custom calibration folder path
```
Example Directory Structure:
```txt
/data/kitti/raw/2011_09_29/     <--- base_dir
├── 2011_09_29_drive_0071_sync  <--- sequence
│   ├── image_00
│   │   ├── data
│   │   │   ├── 0000000000.png
│   │   │   ├── ...
│   │   │   └── 0000001058.png
│   │   └── timestamps.txt
│   ├── image_01
│   │   ├── data
│   │   │   ├── 0000000000.png
│   │   │   ├── ...
│   │   │   └── 0000001058.png
│   │   └── timestamps.txt
│   ├── image_02
│   │   ├── data
│   │   │   ├── 0000000000.png
│   │   │   ├── ...
│   │   │   └── 0000001058.png
│   │   └── timestamps.txt
│   ├── image_03
│   │   ├── data
│   │   │   ├── 0000000000.png
│   │   │   ├── ...
│   │   │   └── 0000001058.png
│   │   └── timestamps.txt
│   ├── oxts
│   │   ├── data
│   │   │   ├── 0000000000.txt
│   │   │   ├── ...
│   │   │   └── 0000001058.txt
│   │   ├── dataformat.txt
│   │   └── timestamps.txt
│   └── velodyne_points
│       ├── data
│       │   ├── 0000000000.bin
│       │   ├── ...
│       │   └── 0000001058.bin
│       ├── timestamps_end.txt
│       ├── timestamps_start.txt
│       └── timestamps.txt
├── calib_cam_to_cam.txt        <--- calibrations
├── calib_imu_to_velo.txt
└── calib_velo_to_cam.txt
```
Note: The `calib_cam_to_cam.txt` file is required to generate the `camera_info` message. Transformation between sensors are defined in the URDF as they are static transformations. For reference, see [kitti_urdf](https://github.com/Chris7462/kitti_urdf).
### 4. Build the package
Use `colcon` to build:
```bash
cd ~/ros2_ws
colcon build --symlink-install --packages-select kitti_dataloader kitti_ros2bag
```
### 5. Run the Converter
```bash
source ./install/setup.bash
ros2 launch kitti_ros2bag kitti_ros2bag_launch.py
```
After successful execution, a bag file named *kitti_2011_09_29_drive_0071_sync_bag* will be generated in your current directory.

## References
1. [ros2_kitti_publishers](https://github.com/umtclskn/ros2_kitti_publishers)
2. [kitti2bag](https://github.com/tomas789/kitti2bag)
