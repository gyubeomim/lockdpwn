ORB_HOME="${HOME}/gitrepo/ORB_SLAM2"

# cd ${ORB_HOME}/Examples/ROS/ORB_SLAM2/

killall stereo_image_proc
rospack profile

case $1 in
	m)
		${ORB_HOME}/Examples/Monocular/mono_kitti ${HOME}/gitrepo/ORB_SLAM2/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/mono_KITTI00-02.yaml ${HOME}/datasets/kitti/data_odometry/sequences/00
		;;
	s)
		${ORB_HOME}/Examples/Stereo/stereo_kitti ${HOME}/gitrepo/ORB_SLAM2/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/stereo_KITTI00-02.yaml ${HOME}/datasets/kitti/data_odometry/sequences/00
		;;
	mros)
		${ORB_HOME}/Examples/ROS/ORB_SLAM2/Mono ${HOME}/gitrepo/ORB_SLAM2/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/KITTI00-02.yaml /camera/image_raw:=/camera/left/image_rect
		;;
	sros)
		ROS_NAMESPACE=camera rosrun stereo_image_proc stereo_image_proc &

		${ORB_HOME}/Examples/ROS/ORB_SLAM2/Stereo ${HOME}/gitrepo/ORB_SLAM2/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/atlas_stereo.yaml 0 /camera/left/image_raw:=/camera/left/image_rect /camera/right/image_raw:=/camera/right/image_rect
		;;
	baglaunch)
		cd ${HOME}/gitrepo/ORB_SLAM2
		${HOME}/gitrepo/ORB_SLAM2/build_ros.sh
		roslaunch ${HOME}/gitrepo/ORB_SLAM2/Examples/ROS/ORB_SLAM2/launch/bag_ros_stereo_orbslam2.launch
		;;
esac
