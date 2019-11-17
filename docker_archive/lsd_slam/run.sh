#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/${USER}/.Xauthority

xhost +local:docker

docker run \
	--runtime=nvidia \
	--net=host \
	--name lsdslam \
    -it \
	--env="XAUTHORITY=${XAUTH}" \
	--env="DISPLAY=unix${DISPLAY}" \
	--env="XDG_RUNTIME_DIR=/run/user/1000" \
	--privileged  \
	-v /run/user/1000:/run/user/1000 \
	-v /dev/bus/usb:/dev/bus/usb \
	-v ${XSOCK}:${XSOCK}:rw \
	-v ${XAUTH}:${XAUTH}:rw \
	-v /home/${USER}/share_docker:/root/share_docker \
	-v /home/${USER}/bag_files:/root/bag_files \
	edward0im/dyrosvehicle:ubuntu_lsd_slam
