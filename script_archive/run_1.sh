if [ ! -d build ]; then
	mkdir build
	cd build
else 
	cd build
fi

case $1 in 
	release)
		cmake -DCMAKE_BUILD_TYPE=Release ..
		;;
	reldeb)
		cd build_reldeb/
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	debug)
		cd build_debug/
		cmake -DCMAKE_BUILD_TYPE=Debug .. 
		;;
esac

make -j12
cd ../

executable="./thirdparty/orb-slam/examples/stereo/example_kitti ./thirdparty/orb-slam/resource/vocabulary/ORBvoc.txt ./thirdparty/orb-slam/examples/stereo/KITTI03.yaml /home/atlas1/datasets/kitti/data_odometry/sequences/00 0 0"

case $1 in
	release)
		$executable
		;;
	reldeb)
		$executable
		;;
	debug)
		gdb --ex="set print thread-events off" --ex="r" -args $executable
esac
