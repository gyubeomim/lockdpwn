

case $1 in
	0)
		/media/data/gitrepo/openvslam-sandbox/build/run_kitti_slam \
			-v /media/data/gitrepo/openvslam-sandbox/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c /media/data/gitrepo/openvslam-sandbox/example/kitti/KITTI_mono_00-02.yaml
		;;
	1)
		/media/data/gitrepo/openvslam-sandbox/build/run_video_slam \
			-v /media/data/gitrepo/openvslam-sandbox/orb_vocab.dbow2 
		;;
	ros)
		source ~/gitrepo/openvslam-sandbox/ros/devel/setup.bash
		rosrun openvslam run_slam \
		-v /media/data/gitrepo/openvslam-sandbox/orb_vocab.dbow2 \
		-c /media/data/gitrepo/openvslam-sandbox/example/dyros_half.yaml
		;;
esac
