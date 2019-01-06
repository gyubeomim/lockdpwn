docker run \
           --runtime=nvidia \
		   --net=host \
		   --name segmap_docker \
		   -it \
		   -v /home/dyros-vehicle/docker:/root/docker \
		   -v /media/dyros-data/bag_files:/root/bag_files \
		   edward0im/dyrosvehicle:ubuntu_cuda9.0
