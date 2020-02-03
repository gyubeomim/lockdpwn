export DSO_PATH=${HOME}/gitrepo/dso-sandbox

case $1 in
	rd)
		cd ${DSO_PATH}/reldebug
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j7
		DSO_FINAL_PATH=${DSO_PATH}/reldebug
		;;
	d)
		cd ${DSO_PATH}/debug
		cmake -DCMAKE_BUILD_TYPE=Debug ..
		make -j7
		DSO_FINAL_PATH=${DSO_PATH}/debug
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
		DSO_FINAL_PATH=${DSO_PATH}/reldebug
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
		DSO_FINAL_PATH=${DSO_PATH}/debug
		;;
esac

executable="${DSO_FINAL_PATH}/bin/dso_dataset \
	files=${HOME}/dataset/kitti/data_odometry/sequences/00/image_0 \
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
		gdb --ex="set print thread-events off" --ex="b CoarseTracker.cpp:352" --ex="r" -args $executable
		;;
esac
