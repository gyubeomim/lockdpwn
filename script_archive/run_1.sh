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
	rdonly)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	rdtest)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	d)
		cmake -DCMAKE_BUILD_TYPE=Debug .. 
		;;
	donly)
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
			/home/atlas1/datasets/kitti/data_odometry/sequences/03 0 0"

executable_test="./thirdparty/orb-slam/examples/stereo/unit_tests"

executable_intern="/home/atlas1/gitrepo/orb-sandbox/thirdparty/intern-sandbox/build/example_kitti ../orb-slam/resource/vocabulary/ORBvoc.txt ../orb-slam/examples/stereo/KITTI00-02.yaml 	/home/atlas1/datasets/kitti/data_odometry/sequences/00 0 0"

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
	rdtest)
		$executable_test
		;;
	d)
		gdb --ex="set print thread-events off" --ex="b LoopClosing.cc:102" --ex="r" -args $executable
		;;
esac

