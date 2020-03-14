#!/bin/sh

docker run \
       --runtime=nvidia \
	   --name=docker_deeplabv3plus \
       -it \
       -p 7777:8888 \
       -v ~/share_docker:/root/share_docker \
       -v /media/dyros-data/datasets:/root/datasets \
       -v /media/dyros-data/bag_files:/root/bag_files \
	   edward0im/dyrosvehicle:ubuntu_deeplabv3plus
       /bin/bash
