rosrun dso_ros conv_dso_live \
	image:=/camera/image_rect \
	calib=~/catkin_ws/config/dso/camera3.txt \ 
	gamma=~/catkin_ws/config/dso/pcalib.txt  \
	vignette=~/catkin_ws/config/dso/vignette.png
