


case $1 in
	rd)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j

		executable="/media/data/gitrepo/openvslam-sandbox/reldebug/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c /media/data/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml"

		gdb --ex="set print thread-events off" --ex="r" -args $executable
		;;
	d)
		cmake -DCMAKE_BUILD_TYPE=Debug ..
		make -j

		executable="/media/data/gitrepo/openvslam-sandbox/debug/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c /media/data/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml"

		gdb --ex="set print thread-events off" --ex="r" -args $executable
		;;

	rdd)  # make directory
		if [ ! -d reldebug ]; then
			mkdir reldebug
			cd reldebug
		else
			cd reldebug
		fi

		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j

		executable="/media/data/gitrepo/openvslam-sandbox/reldebug/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c /media/data/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml"

		gdb --ex="set print thread-events off" --ex="r" -args $executable
		;;
	dd) # make directory
		if [ ! -d debug ]; then
			mkdir debug
			cd debug
		else
			cd debug
		fi

		cmake -DCMAKE_BUILD_TYPE=Debug ..
		make -j

		executable="/media/data/gitrepo/openvslam-sandbox/debug/run_kitti_slam \
			-v /media/data/weights/orb_vocab.dbow2 \
			-d /media/data/dataset/kitti/data_odometry/sequences/00 \
			-c /media/data/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml"

		gdb --ex="set print thread-events off" --ex="r" -args $executable
		;;
esac
