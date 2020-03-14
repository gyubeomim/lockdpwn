#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=${HOME}/.Xauthority

xhost +local:docker

case $1 in 
	cpu)
		docker run \
			--net=host \
			--name starlaw-lcsd-slam \
			-it \
			--env="XAUTHORITY=${XAUTH}" \
			--env="DISPLAY=unix${DISPLAY}" \
			--env="XDG_RUNTIME_DIR=/run/user/1000" \
			--privileged  \
			-v /run/user/1000:/run/user/1000 \
			-v /dev/bus/usb:/dev/bus/usb \
			-v ${XSOCK}:${XSOCK}:rw \
			-v ${XAUTH}:${XAUTH}:rw \
			-v ${HOME}/share_docker:/root/share_docker \
			-v /media/data/dataset:/root/dataset \
			--expose 22 \
			edward0im/starlaw:lcsd-slam
		;;
	*)
		docker run \
			--runtime=nvidia \
			--net=host \
			--name starlaw-lcsd-slam \
			-it \
			--env="XAUTHORITY=${XAUTH}" \
			--env="DISPLAY=unix${DISPLAY}" \
			--env="XDG_RUNTIME_DIR=/run/user/1000" \
			--privileged  \
			-v /run/user/1000:/run/user/1000 \
			-v /dev/bus/usb:/dev/bus/usb \
			-v ${XSOCK}:${XSOCK}:rw \
			-v ${XAUTH}:${XAUTH}:rw \
			-v ${HOME}/share_docker:/root/share_docker \
			-v /media/data/dataset:/root/dataset \
			--expose 22 \
			edward0im/starlaw:lcsd-slam
		;;
esac


#deprecated
# -v /media/data/gitrepo/dv_ws/dyros_ws/docker_ws/src_ubuntu_cuda9.0:/root/docker_ws/src \
	# -v /media/data/gitrepo/dv_ws/dyros_ws/docker_ws/not_used_ubuntu_cuda9.0:/root/docker_ws/not_used \
	# -v /media/data/bag_files:/root/bag_files \
	# -v /usr/local/cuda-10.1:/usr/local/cuda-10.1 \
