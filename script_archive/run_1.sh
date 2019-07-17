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
	reldebonly)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	reldeb)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	reldeb2)
		cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
		;;
	debug)
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
	reldeb2)
		gdb --ex="set print thread-events off"  --ex="r" -args $executable
		;;
	debug)
		gdb --ex="set print thread-events off" --ex="b example_kitti.cc:56" --ex="b ORBmatcher.cc:159" --ex="b ORBmatcher.cc:522" --ex="r" -args $executable
esac

#ARCHIVE
# gdb --ex="set print thread-events off" --ex="r" -args $executable
# gdb --ex="set print thread-events off" --ex="b example_kitti.cc:56" --ex="b ORBmatcher.cc:159" --ex="b ORBmatcher.cc:522" --ex="r" -args $executable
# gdb --ex="set print thread-events off" --ex="b BRIEFdescriptor.cc:118"  --ex="r" -args $executable
