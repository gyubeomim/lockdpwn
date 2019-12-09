

case $1 in
	r) # semi-direct kitti seq 0
		~/gitrepo/openvslam-sandbox/build/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c ~/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml
		;;
	rd) # semi-direct kitti seq 0
		~/gitrepo/openvslam-sandbox/reldebug/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c ~/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml
		;;
	d) # semi-direct kitti seq 0
		~/gitrepo/openvslam-sandbox/debug/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c ~/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml
		;;

	orig) # (original) kitti seq 0
		~/gitrepo/openvslam/build/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c ~/gitrepo/openvslam/example/kitti/KITTI_stereo_00-02.yaml
		;;

	ros)
		source ~/gitrepo/openvslam-sandbox/ros/devel/setup.bash
		rosrun openvslam run_slam \
		-v /media/data/weights/orb_vocab.dbow2 \
		-c ~/gitrepo/openvslam-sandbox/example/dyros_half.yaml
		;;

	oros) # (original) 
		source ~/gitrepo/openvslam/ros/devel/setup.bash
		rosrun openvslam run_slam \
		-v /media/data/weights/orb_vocab.dbow2 \
		-c ~/gitrepo/openvslam/example/dyros_half.yaml
		;;
esac
