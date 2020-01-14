export DSO_PATH=${HOME}/gitrepo/dso-sandbox

case $1 in
	r)
		cd ${DSO_PATH}/build
		cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
		make -j6
		;;
	rmac)
		cd ${DSO_PATH}/build
		cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
		make -j6
		;;
	rd)
		cd ${DSO_PATH}/reldebug
		cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		make -j6
		;;
	d)
		cd ${DSO_PATH}/debug
		cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug ..
		make -j6
		;;
esac

executable="${DSO_PATH}/build/bin/dso_dataset \
			files=/media/data/dataset/kitti/data_odometry/sequences/00/image_0 \
			calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt \
			gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
			vignette=${HOME}/catkin_ws/config/dso/vignette.png \
			preset=0 \
			speed=1 \
			mode=1"

executable_mac="${DSO_PATH}/build/bin/dso_dataset \
	files=${HOME}/dataset/kitti/data_odometry/sequences/00/image_0 \
	calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt \
	gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
	vignette=${HOME}/catkin_ws/config/dso/vignette.png \
	preset=0 \
	speed=1 \
	mode=1"

case $1 in
	r)
		$executable
		;;
	rd)
		# gdb --ex="set print thread-events off" --ex="b ImageRW_OpenCV.cpp:35" --ex="r" -args ${executable}
		# gdb --ex="set print thread-events off" --ex="b DatasetReader.h:283" --ex="r" -args ${executable}
		gdb --ex="set print thread-events off" --ex="r" -args ${executable}
		;;
	d)
		gdb --ex="set print thread-events off" --ex="r" -args ${executable}
		;;
	rmac)
		$executable_mac
		;;
esac
# set speed=1 to play with real-time. otherwise, it plays as fast as possible.
