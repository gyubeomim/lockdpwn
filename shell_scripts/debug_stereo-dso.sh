export STEREODSO_PATH=${HOME}/gitrepo/stereo-dso-sandbox

case $1 in
	rd)
		cd ${STEREODSO_PATH}/reldebug
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j7
		STEREODSO_FINAL_PATH=${STEREODSO_PATH}/reldebug
		;;
	d)
		cd ${STEREODSO_PATH}/debug
		cmake -DCMAKE_BUILD_TYPE=Debug ..
		make -j7
		STEREODSO_FINAL_PATH=${STEREODSO_PATH}/debug
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
		STEREODSO_FINAL_PATH=${STEREODSO_PATH}/reldebug
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
		STEREODSO_FINAL_PATH=${STEREODSO_PATH}/debug
		;;
esac

executable="${STEREODSO_FINAL_PATH}/bin/dso_dataset \
	files=${HOME}/dataset/kitti/data_odometry/sequences/00 \
	calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt \
	gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
	vignette=${HOME}/catkin_ws/config/dso/vignette.png \
	preset=0 \
	speed=1 \
	mode=1"

case $2 in
	0)
		gdb --ex="set print thread-events off" --ex="r" -args $executable
		;;
	1)
		gdb --ex="set print thread-events off" --ex="b CoarseTracker.cpp:1015" --ex="r" -args $executable
		;;
	2)
		gdb --ex="set print thread-events off" --ex="b CoarseTracker.cpp:927" --ex="r" -args $executable
		;;
	3)
		gdb --ex="set print thread-events off" --ex="b dso_g2o_edge.cpp:linearizeOplus()" --ex="b dso_g2o_edge.cpp:computeError()" --ex="r" -args $executable
		;;
	4)
		gdb --ex="set print thread-events off" --ex="b dso_g2o_edge.cpp:linearizeOplus()" --ex="r" -args $executable
		;;
	5)
		gdb --ex="set print thread-events off" --ex="b linear_solver_eigen.h:92()" --ex="r" -args $executable
		;;
	l0)
		lldb -o run -- $executable
		;;
esac
