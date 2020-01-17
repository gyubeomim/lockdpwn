case $1 in
	rd)
		cd ${HOME}/gitrepo/openvslam-sandbox/reldebug
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j7
		;;
	d)
		cd ${HOME}/gitrepo/openvslam-sandbox/debug
		cmake -DCMAKE_BUILD_TYPE=Debug ..
		make -j7
		;;

	rdd)  # make directory
		if [ ! -d reldebug ]; then
			mkdir reldebug
			cd reldebug
		else
			cd reldebug
		fi

		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j7
		;;
	dd) # make directory
		if [ ! -d debug ]; then
			mkdir debug
			cd debug
		else
			cd debug
		fi

		cmake -DCMAKE_BUILD_TYPE=Debug ..
		make -j7
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
	3)
		gdb --ex="set print thread-events off" --ex="b pose_optimizer.cc:13" --ex="r" -args $executable
		;;
	4)
		gdb --ex="set print thread-events off" --ex="b direct_method_utils.cc:157" --ex="r" -args $executable
		;;
	5)
		gdb --ex="set print thread-events off" --ex="b direct_perspective_pose_opt_edge.cc:8" --ex="r" -args $executable
		;;
	6)
		gdb --ex="set print thread-events off" --ex="b ImageRW_dummy.cpp:35" --ex="r" -args $executable
		;;
esac
