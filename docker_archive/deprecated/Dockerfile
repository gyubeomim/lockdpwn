FROM ros:kinetic-perception

RUN apt-get update && apt-get install -y \
	python-catkin-pkg python-rosdep python-wstool \
	python-catkin-tools ros-kinetic-catkin \
	&& rm -rf /var/lib/apt/lists

ENV CATKIN_WS=/root/catkin_ws
RUN rm /bin/sh \
	&& ln -s /bin/bash /bin/sh	

RUN apt-get update && apt-get install -y \
	build-essential software-properties-common \
	doxygen autoconf \
	&& rm -rf /var/lib/apt/lists	

RUN source /ros_entrypoint.sh \
	&& mkdir -p $CATKIN_WS/src \
	&& cd $CATKIN_WS/src && git clone https://github.com/ICRA2017/segmap.git \
	&& wstool init \
	&& wstool merge segmap/dependencies.rosinstall \
	&& wstool update

RUN apt-get update && apt-get install -y \
	libeigen3-dev libflann-dev libtool \
	mesa-common-dev mesa-utils-extra libgl1-mesa-dev libglapi-mesa \
	&& rm -rf /var/lib/apt/lists	
	
RUN apt-get update && apt-get install -y \
	ros-kinetic-geometry\
	&& rm -rf /var/lib/apt/lists
	
RUN source /ros_entrypoint.sh \
	&& cd $CATKIN_WS \
	&& catkin build -DCMAKE_BUILD_TYPE=Release segmapper