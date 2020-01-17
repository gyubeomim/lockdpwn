#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/$USER/.Xauthority

xhost +local:docker

docker run \
	--runtime=nvidia \
	--net=host \
	--name docker_second \
	-it \
	--env="XAUTHORITY=${XAUTH}" \
	--env="DISPLAY=unix$DISPLAY" \
	--env="XDG_RUNTIME_DIR=/run/user/1000" \
	--privileged  \
	-v /run/user/1000:/run/user/1000 \
	-v /dev/bus/usb:/dev/bus/usb \
	-v $XSOCK:$XSOCK:rw \
	-v $XAUTH:$XAUTH:rw \
	-v /home/dyros-vehicle/share_docker:/root/share_docker \
	-v /media/dyros-data/bag_files:/root/bag_files \
	-v /media/dyros-data/datasets/kitti/data_object:/root/data \
	-v /media/dyros-data/pretrained_weights/second_pretrained_model_v1.5:/root/model \
	edward0im/dyrosvehicle:ubuntu_second 
