#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/$USER/.Xauthority

docker run \
    --runtime=nvidia \
    -it \
    --net=host \
	--name autoware_docker \
    --env="XAUTHORITY=${XAUTH}" \
    --env="DISPLAY=${DISPLAY}" \
    -v $XSOCK:$XSOCK:rw \
    -v $XAUTH:$XAUTH:rw \
    -v $HOST_DIR:$SHARED_DIR:rw \
    --privileged -v /dev/bus/usb:/dev/bus/usb \
	-v /home/dyros-vehicle/docker:/home/autoware/docker \
	-v /media/dyros-data/bag_files:/home/autoware/bag_files \
	edward0im/dyrosvehicle:ubuntu_autoware
