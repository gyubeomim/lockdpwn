killall stereo_image_proc

cd ${HOME}/gitrepo/stereo-dso-sandbox/build && make -j

cd ${HOME}/catkin_ws && catkin_make

ROS_NAMESPACE=camera rosrun stereo_image_proc stereo_image_proc &

rosrun stereo_dso_ros stero_dso_ros \
	calib=${HOME}/catkin_ws/config/dso/camera2.txt \
	gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
	vignette=${HOME}/catkin_ws/config/dso/vignette.png \
	preset=0 \
	mode=1 
