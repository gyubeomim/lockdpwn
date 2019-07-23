if [ ! -d build ]; then
	mkdir build
	cd build
else 
	cd build
fi

case $1 in 
	r)
		cmake -DCMAKE_BUILD_TYPE=Release ..
		;;
	rdonly)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	rd)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	rdintern)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	rd2)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	d)
		cmake -DCMAKE_BUILD_TYPE=Debug .. 
		;;
	dintern)
		cmake -DCMAKE_BUILD_TYPE=Debug ..
		;;
esac

make -j12
cd ../

executable="./thirdparty/orb-slam/examples/stereo/example_kitti 
			./thirdparty/orb-slam/resource/vocabulary/ORBvoc.txt 
			./thirdparty/orb-slam/examples/stereo/KITTI03.yaml 
			/home/atlas1/datasets/kitti/data_odometry/sequences/00 0 0"

executable_intern="/home/atlas1/gitrepo/orb-sandbox/thirdparty/intern-sandbox/build/example_kitti ../orb-slam/resource/vocabulary/ORBvoc.txt ../orb-slam/examples/stereo/KITTI03.yaml 	/home/atlas1/datasets/kitti/data_odometry/sequences/00 0 0"

case $1 in
	r)
		$executable
		;;
	rd)
		$executable
		;;
	rdintern)
		$executable_intern
		;;
	rd2)
		gdb --ex="set print thread-events off"  --ex="r" -args $executable
		;;
	d)
		gdb --ex="set print thread-events off" --ex="b example_kitti.cc:177" --ex="r" -args $executable
esac

