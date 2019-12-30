
if [ -z "$1" ] 
then
	sec=0
else
	sec=$1
fi

case $2 in
	raw)
		rosbag play ${HOME}/bag_files/kitti/kitti_odometry_sequence_00.bag 	kitti/camera_color_right/image:=/camera/right/image_raw kitti/camera_color_left/image:=/camera/left/image_raw kitti/camera_color_right/camera_info:=/camera/right/camera_info kitti/camera_color_left/camera_info:=/camera/left/camera_info kitti/camera_gray_left/image:=/camera/left/image_rect_gray -s${sec}
		;;
	*)
		rosbag play ${HOME}/bag_files/kitti/kitti_odometry_sequence_00.bag 	kitti/camera_color_right/image:=/camera/right/image_rect kitti/camera_color_left/image:=/camera/left/image_rect kitti/camera_color_right/camera_info:=/camera/right/camera_info kitti/camera_color_left/camera_info:=/camera/left/camera_info kitti/camera_gray_left/image:=/camera/left/image_rect_gray -s${sec}
		;;
esac
