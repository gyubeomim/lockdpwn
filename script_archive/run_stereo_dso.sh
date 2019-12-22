export STEREODSO_PATH=${HOME}/gitrepo/stereo-dso

seq=$1

${STEREODSO_PATH}/build/bin/dso_dataset \
	files=/media/data/dataset/kitti/data_odometry/sequences/${seq} \
	calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt \
	gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
	vignette=${HOME}/catkin_ws/config/dso/vignette.png \
	preset=0 \
	mode=1
