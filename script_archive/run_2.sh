
sequence=$1

# run ORB_SLAM2
rosrun ORB_SLAM2 Mono ORB_SLAM2/Vocabulary/ORBvoc.txt ORB_SLAM2/Examples/Monocular/TUMmonoVO_yaml/monoVO_ORB_SLAM_full_$sequence.yaml &

# run dso_ros
source DSO_ROS/catkin_ws/devel/setup.bash
roslaunch dso_ros monoVO_seong_$sequence.launch
