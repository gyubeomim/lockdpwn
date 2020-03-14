#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=${HOME}/.Xauthority

xhost +local:docker

case $1 in
	cpu)
		LDPRELOAD=${HOME}/.empty
		X8664LINUXGNU=${HOME}/gitrepo/lockdpwn/docker/util/x86_64-linux-gnu.intel
		touch ${LDPRELOAD}

		docker run \
			--net=host \
			--name starlaw-slam1 \
			-it \
			--env="XAUTHORITY=${XAUTH}" \
			--env="DISPLAY=unix${DISPLAY}" \
			--env="XDG_RUNTIME_DIR=/run/user/1000" \
			--privileged  \
			-v /run/user/1000:/run/user/1000 \
			-v /dev/bus/usb:/dev/bus/usb \
			-v ${XSOCK}:${XSOCK}:rw \
			-v ${XAUTH}:${XAUTH}:rw \
			-v ${LDPRELOAD}:/etc/ld.so.preload \
			-v ${X8664LINUXGNU}:/usr/local/lib/x86_64-linux-gnu \
			-v ${HOME}/share_docker:/root/share_docker \
			--expose 22 \
			edward0im/starlaw:slam1
		;;
	*)
		LDPRELOAD=${HOME}/gitrepo/lockdpwn/docker/util/ld.so.preload
		X8664LINUXGNU=${HOME}/gitrepo/lockdpwn/docker/util/x86_64-linux-gnu
		
		docker run \
			--runtime=nvidia \
			--net=host \
			--name starlaw-slam1 \
			-it \
			--env="XAUTHORITY=${XAUTH}" \
			--env="DISPLAY=unix${DISPLAY}" \
			--env="XDG_RUNTIME_DIR=/run/user/1000" \
			--privileged  \
			-v /run/user/1000:/run/user/1000 \
			-v /dev/bus/usb:/dev/bus/usb \
			-v ${XSOCK}:${XSOCK}:rw \
			-v ${XAUTH}:${XAUTH}:rw \
			-v ${LDPRELOAD}:/etc/ld.so.preload \
			-v ${X8664LINUXGNU}:/usr/local/lib/x86_64-linux-gnu \
			-v ${HOME}/share_docker:/root/share_docker \
			--expose 22 \
			edward0im/starlaw:slam1
		;;
esac



#deprecated
# -v /media/data/gitrepo/dv_ws/dyros_ws/docker_ws/src_ubuntu_cuda9.0:/root/docker_ws/src \
# -v /media/data/gitrepo/dv_ws/dyros_ws/docker_ws/not_used_ubuntu_cuda9.0:/root/docker_ws/not_used \
# -v /media/data/bag_files:/root/bag_files \
