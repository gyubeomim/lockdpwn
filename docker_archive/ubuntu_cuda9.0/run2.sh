#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/$USER/.Xauthority

xhost +local:docker

	# -v /media/dyros-data/gitrepo/ims_ros/docker_ws/src_ubuntu_cuda9.0:/root/docker_ws/src \
	# -v /media/dyros-data/gitrepo/ims_ros/docker_ws/not_used_ubuntu_cuda9.0:/root/docker_ws/not_used \
	# -v /media/dyros-data/bag_files:/root/bag_files \
docker run \
	--runtime=nvidia \
	--net=host \
	--name docker_cuda9.0 \
	-it \
	--env="XAUTHORITY=${XAUTH}" \
	--env="DISPLAY=unix$DISPLAY" \
	--env="XDG_RUNTIME_DIR=/run/user/1000" \
	--privileged  \
	-v /run/user/1000:/run/user/1000 \
	-v /dev/bus/usb:/dev/bus/usb \
	-v $XSOCK:$XSOCK:rw \
	-v $XAUTH:$XAUTH:rw \
	-v /home/$USER/share_docker:/root/share_docker \
	--expose 22 \
	edward0im/dyrosvehicle:ubuntu_cuda9.0
