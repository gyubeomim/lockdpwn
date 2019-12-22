case $1 in
	rd)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j
		;;
	d)
		cmake -DCMAKE_BUILD_TYPE=Debug ..
		make -j
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
		;;
esac

executable="${HOME}/gitrepo/openvslam-sandbox/reldebug/run_kitti_slam \
	-v /media/data/weights/orb_vocab.dbow2 \
	-d /media/data/dataset/kitti/data_odometry/sequences/00 \
	-c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml"

case $2 in
	0)
		gdb --ex="set print thread-events off" --ex="r" -args $executable
		;;
	1)
		gdb --ex="set print thread-events off" --ex="b tracking_module.cc:856" --ex="r" -args $executable
		;;
	2)
		gdb --ex="set print thread-events off" --ex="b pose_opt_edge_wrapper.h:107" --ex="r" -args $executable
		;;
esac
