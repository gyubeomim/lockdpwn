#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/${USER}/.Xauthority

xhost +local:docker

docker run \
	--runtime=nvidia \
	--net=host \
	--name starlaw-slam1-orb \
	--rm \
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
	--expose 22 \
	edward0im/starlaw:slam1 \
	/root/run_orbslam.sh


#deprecated
# -v /media/data/gitrepo/dv_ws/dyros_ws/docker_ws/src_ubuntu_cuda9.0:/root/docker_ws/src \
# -v /media/data/gitrepo/dv_ws/dyros_ws/docker_ws/not_used_ubuntu_cuda9.0:/root/docker_ws/not_used \
# -v /media/data/bag_files:/root/bag_files \
