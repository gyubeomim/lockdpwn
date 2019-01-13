#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/$USER/.Xauthority

xhost +local:docker

docker run \
	--runtime=nvidia \
	--net=host \
	--name segmap_docker \
	-it \
	--env="XAUTHORITY=${XAUTH}" \
	--env="DISPLAY=unix$DISPLAY" \
	--env="XDG_RUNTIME_DIR=/run/user/1000" \
	--privileged  \
	-v /run/user/1000:/run/user/1000 \
	-v /dev/bus/usb:/dev/bus/usb \
	-v $XSOCK:$XSOCK:rw \
	-v $XAUTH:$XAUTH:rw \
	-v /home/dyros-vehicle/docker:/root/docker \
	-v /media/dyros-data/bag_files:/root/bag_files \
	edward0im/dyrosvehicle:ubuntu_cuda9.0
