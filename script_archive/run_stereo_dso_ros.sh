killall stereo_image_proc

ROS_NAMESPACE=camera rosrun stereo_image_proc stereo_image_proc &

rosrun stereo_dso_ros stero_dso_ros \
	calib=${HOME}/catkin_ws/config/dso/camera2.txt \
	gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
	vignette=${HOME}/catkin_ws/config/dso/vignette.png \
	preset=0 \
	mode=1 \
	/cam0/image_raw:=/camera/left/image_rect \
	/cam1/image_raw:=/camera/right/image_rect
