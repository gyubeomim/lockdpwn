if [ -z "$1" ]; then
	echo "Usage: run_bag_without_camera_info.sh {bagfile}"
else
	case $2 in
		1)
			rosbag play $1 --topic /camera/left/image_raw /camera/right/image_raw -r0.1 -l -s14 -u1
			;;
		*)
			rosbag play $1 --topic /camera/left/image_raw /camera/right/image_raw -r0.2 -l
			;;
	esac
fi
