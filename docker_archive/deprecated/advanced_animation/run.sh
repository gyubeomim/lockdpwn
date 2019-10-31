#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/$USER/.Xauthority

xhost +local:docker

docker run \
	--runtime=nvidia \
	--net=host \
	-it \
	-e SHELL\
	-e "XAUTHORITY=${XAUTH}" \
	-e "DISPLAY=unix$DISPLAY" \
	-e "XDG_RUNTIME_DIR=/run/user/1000" \
	--privileged  \
	-v /run/user/1000:/run/user/1000 \
	-v /dev/bus/usb:/dev/bus/usb \
	-v $XSOCK:$XSOCK:rw \
	-v $XAUTH:$XAUTH:rw \
	--name adv_animation \
	edward0im/adv_animation:0
