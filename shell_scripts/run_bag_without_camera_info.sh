if [ -z "$1" ]; then
	echo "Usage: run_bag_without_camera_info.sh {bagfile}"
else
	rosbag play $1 --topic /camera/left/image_raw /camera/right/image_raw
fi
