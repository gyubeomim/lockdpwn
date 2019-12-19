rosbag play ~/bag_files/kitti/kitti_odometry_sequence_00.bag \
	kitti/camera_color_right/image:=/camera/right/image_rect kitti/camera_color_left/image:=/camera/left/image_rect kitti/camera_color_right/camera_info:=/camera/right/camera_info kitti/camera_color_left/camera_info:=/camera/left/camera_info
