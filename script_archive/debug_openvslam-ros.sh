
if [ $1 != "rdall" ] && [ $1 != "rdallfull" ] && [ $1 != "r" ]; then
	cd ${HOME}/debug_ws 
	catkin_make -DCMAKE_BUILD_TYPE=RelWithDebInfo
fi


case $1 in
	r)
		cd ${HOME}/debug_ws 
		rm build/ devel/ -rf
		catkin_make -DCMAKE_BUILD_TYPE=Release
		source devel/setup.bash
		rospack profile
		${HOME}/debug_ws/devel/lib/openvslam-ros/run_semi_direct -v /media/data/weights/orb_vocab.dbow2 -c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt gamma=${HOME}/catkin_ws/config/dso/pcalib.txt vignette=${HOME}/catkin_ws/config/dso/vignette.png preset=0 mode=1
		;;
	rd)
		source devel/setup.bash
		rospack profile
		roslaunch openvslam-ros run_semi_direct_debug.launch
		;;
	rdfull)
		source devel/setup.bash
		rospack profile
		roslaunch openvslam-ros run_semi_direct_debug_nohalf.launch
		;;
	rd2)
		gdb --ex="b EnergyFunctional.cpp:379" --ex="r" --args ${HOME}/debug_ws/devel/lib/openvslam-ros/run_semi_direct -v /media/data/weights/orb_vocab.dbow2 -c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt gamma=${HOME}/catkin_ws/config/dso/pcalib.txt vignette=${HOME}/catkin_ws/config/dso/vignette.png preset=0 speed=1 mode=1
		;;

	rdall)
		cd ${HOME}/gitrepo/openvslam-sandbox/reldebug
		make -j
		cd ${HOME}/gitrepo/stereo-dso-sandbox/build
		make -j
		cd ${HOME}/debug_ws 
		catkin_make -DCMAKE_BUILD_TYPE=RelWithDebInfo
		source devel/setup.bash
		rospack profile
		roslaunch openvslam-ros run_semi_direct_debug.launch
		;;
	rdallfull)
		cd ${HOME}/gitrepo/openvslam-sandbox/reldebug
		make -j
		cd ${HOME}/gitrepo/stereo-dso-sandbox/build
		make -j
		cd ${HOME}/debug_ws 
		catkin_make -DCMAKE_BUILD_TYPE=RelWithDebInfo
		source devel/setup.bash
		rospack profile
		roslaunch openvslam-ros run_semi_direct_debug_nohalf.launch
		;;
esac



#deprecated
		# gdb --ex="r" --args ${HOME}/debug_ws/devel/lib/openvslam-ros/run_semi_direct -v /media/data/weights/orb_vocab.dbow2 -c ${HOME}/catkin_ws/config/semi-direct/KITTI_stereo_half_00-02.yaml calib=${HOME}/catkin_ws/config/semi-direct/camera_half_kitti.txt gamma=${HOME}/catkin_ws/config/dso/pcalib.txt vignette=${HOME}/catkin_ws/config/dso/vignette.png preset=0 speed=1 mode=1

	# rdfull3)
	# 	cd ${HOME}/gitrepo/openvslam-sandbox/reldebug
	# 	make -j
	# 	cd ${HOME}/gitrepo/stereo-dso-sandbox/build
	# 	make -j
	# 	cd ${HOME}/debug_ws 
	# 	catkin_make -DCMAKE_BUILD_TYPE=RelWithDebInfo
	# 	gdb --ex="b FullSystem.cpp:1004" --ex="r" --args ${HOME}/debug_ws/devel/lib/openvslam-ros/run_semi_direct -v /media/data/weights/orb_vocab.dbow2 -c ${HOME}/gitrepo/openvslam-sandbox/example/kitti/KITTI_stereo_00-02.yaml calib=${HOME}/catkin_ws/config/dso/camera_kitti.txt gamma=${HOME}/catkin_ws/config/dso/pcalib.txt vignette=${HOME}/catkin_ws/config/dso/vignette.png preset=0 mode=1
	# 	;;
