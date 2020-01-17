rosrun dso_ros dso_live \
	image:=/camera/image_rect \
	calib=~/catkin_ws/config/dso/camera2.txt
	gamma=~/catkin_ws/config/dso/pcalib.txt
	vignette=~/catkin_ws/config/dso/vignette.png
