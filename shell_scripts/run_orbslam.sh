ORB_HOME="${HOME}/gitrepo/orbslam2-sandbox"

cd ${ORB_HOME}/build
make -j$(nproc-1)
cd ~/catkin_ws
catkin_make

rospack profile

case $1 in
    m)
        ${ORB_HOME}/Examples/Monocular/mono_kitti ${ORB_HOME}/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/mono_KITTI00-02.yaml ${HOME}/dataset/kitti/data_odometry/sequences/00
        ;;
    s)
        ${ORB_HOME}/Examples/Stereo/stereo_kitti ${ORB_HOME}/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/stereo_KITTI00-02.yaml ${HOME}/dataset/kitti/data_odometry/sequences/00
        ;;
    bag)
        roslaunch orbslam2_ros bag_ros_stereo_orbslam2.launch
	;;
esac


# mros)
# 	${ORB_HOME}/Examples/ROS/ORB_SLAM2/Mono ${ORB_HOME}/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/KITTI00-02.yaml /camera/image_raw:=/camera/left/image_rect
# 	;;
# sros)
# 	${ORB_HOME}/Examples/ROS/ORB_SLAM2/Stereo ${ORB_HOME}/Vocabulary/ORBvoc.txt ${HOME}/catkin_ws/config/orb/dv.yaml 0 /camera/left/image_raw:=/camera/left/image_rect /camera/right/image_raw:=/camera/right/image_rect
# 	;;
