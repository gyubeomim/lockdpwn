#!/bin/sh
XSOCK=/tmp/.X11-unix
XAUTH=/home/$USER/.Xauthority

	# -v /home/dyros-vehicle/docker:~/docker \
	# -v /media/dyros-data/datasets:~/datasets \
	# -v /media/dyros-data/bag_files:~/bag_files \

docker run \
	--rm \
    --runtime=nvidia \
    -it \
    --net=host \
	--name anonymous_docker \
    --env="XAUTHORITY=${XAUTH}" \
    --env="DISPLAY=${DISPLAY}" \
	--env="XDG_RUNTIME_DIR=/run/user/1000" \
    --privileged \
	-v /run/user/1000:/run/user/1000 \
	-v /dev/bus/usb:/dev/bus/usb \
    -v $XSOCK:$XSOCK:rw \
    -v $XAUTH:$XAUTH:rw \
    -v $HOST_DIR:$SHARED_DIR:rw \
	luca911014/frustum-pointnet:0.0.1
