rosrun dso_ros dso_live \
	image:=/camera/image_rect \
	calib=~/catkin_ws/config/dso/camera3.txt \
	gamma=~/catkin_ws/config/dso/pcalib_tum.txt  \
	vignette=~/catkin_ws/config/dso/vignette_tum.png
