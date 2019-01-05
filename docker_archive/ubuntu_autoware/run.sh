docker run \
           --runtime=nvidia \
		   --net=host \
		   --name autoware_docker \
		   --it \
		   -v /home/dyros-vehicle/docker:/root/data \
		   edward0im/dyrosvehicle:ubuntu_autoware
