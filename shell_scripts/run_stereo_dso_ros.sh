cd ${HOME}/gitrepo/stereo-dso/build && make -j

cd ${HOME}/catkin_ws && catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=1

case $1 in 
    0)
        rosrun stereo_dso_ros stereo_dso_ros \
               calib=${HOME}/catkin_ws/config/dso/camera_dv.txt \
               gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
               vignette=${HOME}/catkin_ws/config/dso/vignette.png \
               preset=0 \
               mode=1 
        ;;
    1)
        rosrun stereo_dso_ros stereo_dso_ros \
               calib=${HOME}/catkin_ws/config/dso/camera_dv_resize.txt \
               gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
               vignette=${HOME}/catkin_ws/config/dso/vignette.png \
               preset=0 \
               mode=1 
        ;;
    bag) 
        roslaunch stereo_dso_ros bag_stereo_dso_ros.launch
	;;
esac
