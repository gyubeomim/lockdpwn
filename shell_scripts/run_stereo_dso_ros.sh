killall stereo_image_proc

cd ${HOME}/gitrepo/stereo-dso/build && make -j

cd ${HOME}/catkin_ws && catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=1

case $1 in 
	0)
		ROS_NAMESPACE=camera rosrun stereo_image_proc stereo_image_proc &
		rosrun stereo_dso_ros stero_dso_ros \
			calib=${HOME}/catkin_ws/config/dso/camera_atlas.txt \
			gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
			vignette=${HOME}/catkin_ws/config/dso/vignette.png \
			preset=0 \
			mode=1 
		;;
	1)  # run kitti bag file
		ROS_NAMESPACE=camera rosrun stereo_image_proc stereo_image_proc &
		rosrun stereo_dso_ros stero_dso_ros \
			calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt \
			gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
			vignette=${HOME}/catkin_ws/config/dso/vignette.png \
			preset=0 \
			mode=1 
		;;
	baglaunch) # run roslaunch (bag file with stereo-dso)
		roslaunch stereo_dso_ros bag_stereo_dso_ros.launch
		;;
esac
