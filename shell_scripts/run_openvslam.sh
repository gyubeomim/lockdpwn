
if [ "$1" == "r" ]; then
	cd ${HOME}/gitrepo/openvslam-sandbox/build && make -j
elif [ "$1" == "rd" ]; then
	cd ${HOME}/gitrepo/openvslam-sandbox/reldebug && make -j
fi

case $1 in
	r) # semi-direct kitti seq 0
		${HOME}/gitrepo/openvslam-sandbox/build/run_kitti_slam \
			-v ${HOME}/weights/orb_vocab.dbow2 \
			-d ${HOME}/dataset/kitti/data_odometry/sequences/00 \
			-c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml
		;;
	rd) # semi-direct kitti seq 0
		${HOME}/gitrepo/openvslam-sandbox/reldebug/run_kitti_slam \
			-v ${HOME}/weights/orb_vocab.dbow2 \
			-d ${HOME}/dataset/kitti/data_odometry/sequences/00 \
			-c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml
		;;
	d) # semi-direct kitti seq 0
		${HOME}/gitrepo/openvslam-sandbox/debug/run_kitti_slam \
			-v ${HOME}/weights/orb_vocab.dbow2 \
			-d ${HOME}/dataset/kitti/data_odometry/sequences/00 \
			-c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml
		;;

	orig) # (original) kitti seq 0
		${HOME}/gitrepo/openvslam/build/run_kitti_slam \
			-v ${HOME}/weights/orb_vocab.dbow2 \
			-d ${HOME}/dataset/kitti/data_odometry/sequences/00 \
			-c ${HOME}/gitrepo/openvslam/example/kitti/KITTI_stereo_00-02.yaml
		;;

	ros)
		cd ${HOME}/catkin_ws && catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=1
		source ${HOME}/catkin_ws/devel/setup.bash
		rospack profile
		rosrun openvslam-ros run_semi_direct \
		-v ${HOME}/weights/orb_vocab.dbow2 \
		-c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml \
		calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt gamma=${HOME}/catkin_ws/config/dso/pcalib.txt vignette=${HOME}/catkin_ws/config/dso/vignette.png preset=0 mode=1
		;;

	oros) # (original) 
		source ${HOME}/gitrepo/openvslam/ros/devel/setup.bash
		rosrun openvslam run_slam \
		-v ${HOME}/weights/orb_vocab.dbow2 \
		-c ${HOME}/gitrepo/openvslam/example/dyros_half.yaml
		;;
esac

# deprecated===================================================================
	# rosmono)
	# 	cd ${HOME}/gitrepo/openvslam-sandbox/ros/ && catkin_make
	# 	source ${HOME}/gitrepo/openvslam-sandbox/ros/devel/setup.bash
	# 	rospack profile
	# 	rosrun openvslam run_slam \
	# 	-v /media/data/weights/orb_vocab.dbow2 \
	# 	-c ${HOME}/gitrepo/openvslam-sandbox/example/dyros_half.yaml
	# 	;;
