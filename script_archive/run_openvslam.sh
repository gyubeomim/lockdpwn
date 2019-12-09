

case $1 in
	0) # semi-direct kitti seq 0
		/media/data/gitrepo/openvslam-sandbox/build/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c /media/data/gitrepo/openvslam-sandbox/example/kitti/KITTI_mono_00-02.yaml
		;;

	ros)
		source ~/gitrepo/openvslam-sandbox/ros/devel/setup.bash
		rosrun openvslam run_slam \
		-v /media/data/weights/orb_vocab.dbow2 \
		-c /media/data/gitrepo/openvslam-sandbox/example/dyros_half.yaml
		;;

	o1) # (original) kitti seq 0
		/media/data/gitrepo/openvslam/build/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c /media/data/gitrepo/openvslam/example/kitti/KITTI_mono_00-02.yaml
		;;
	oros) # (original) 
		source ~/gitrepo/openvslam/ros/devel/setup.bash
		rosrun openvslam run_slam \
		-v /media/data/weights/orb_vocab.dbow2 \
		-c /media/data/gitrepo/openvslam/example/dyros_half.yaml
		;;
esac
