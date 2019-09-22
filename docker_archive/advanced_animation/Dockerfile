FROM osrf/ros:kinetic-desktop-full
# FROM ubuntu:xenial
# https://github.com/osrf/docker_images/blob/master/ros/kinetic/ubuntu/xenial/ros-core/Dockerfile


ENV LANG en_US.UTF-8

#RUN apt-get update 
# E: Failed to fetch http://security.ubuntu.com/ubuntu/dists/xenial-security/main/binary-amd64/by-hash/SHA256/d704137b4f7ea9cb720a6edaaf484b4333fe18ffd9a3d98395cd4945f2645fec  Hash Sum mismatch

# try1
RUN cat /etc/apt/sources.list
#RUN rm -rf /var/lib/apt/lists/* && apt-get clean
#RUN apt-get update -o 'Acquire::CompressionTypes::Order::=gz' -o 'APT::Get::List-Cleanup="0"' -o 'Acquire::http::Pipeline-Depth=0' -o 'Acquire::http::No-Cache=true' -o 'Acquire::BrokenProxy=true'

# try 2
#RUN rm -rf /var/lib/apt/lists/* 
#RUN apt-get clean && apt-get update 

# try 3
RUN rm -rf /var/lib/apt/lists/* 
#RUN sed -i 's/http:\/\/archive/http:\/\/us.archive/g' /etc/apt/sources.list
# RUN sed -i 's/http:\/\//https:\/\//g' /etc/apt/sources.list
# deb http://security
RUN sed -i -e 's+\(^deb http://security.*\)+# \1+g' /etc/apt/sources.list
RUN apt-get clean && apt-get update 


RUN apt-get install -y \
    tmux \
	    curl \
		    wget \
			    vim \
				    sudo \
					    libgl1-mesa-glx \
						    libgl1-mesa-dri \
							    mesa-utils \
								    unzip \
									    locales \
										    ntp \
											    whois \
												    sudo \
													    ssh

# locale
#RUN sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen \
#     && dpkg-reconfigure --frontend=noninteractive locales \
#     && update-locale LANG=en_US.UTF-8
#ENV LANG en_US.UTF-8
#ENV LANGUAGE en_US:en
#ENV LC_ALL en_US.UTF-8

RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8  

# develop env for visual studio code - not worked with snapd !!!!
#RUN apt-get install -y libnss3 libxkbfile1 libsecret-1-0
#RUN apt-get install -y snapd && snap install code --classic
#RUN apt-get install -y code

# clean up first
#RUN apt-get autoremove --purge --yes && rm -rf /var/lib/apt/lists/*
RUN rm -rf /etc/ros/rosdep/sources.list.d/20-default.list


# rosdep update not with root 
#RUN rosdep init && rosdep update
#RUN rosdep init
#RUN apt-get install python-rosinstall -y
#RUN apt-get install -q -y ros-kinetic-rqt*

# hostname
RUN echo "docker" > /etc/hostname

# HOST_USER from build arguemnt
ARG HOST_USER
ARG UNAME=${HOST_USER}
ARG UID=1000
ARG GID=1000
ARG HOME=/home/${UNAME}
RUN useradd -rm -d ${HOME} -s /bin/bash -g root -G sudo,audio,video,plugdev -u ${UID} ${UNAME}
RUN mkdir -p /etc/sudoers.d && \
    echo "${UNAME} ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/${UNAME} && \
	    chmod 0440 /etc/sudoers.d/${UNAME} 

#RUN chown -R ${UNAME} ${HOME}
USER ${UNAME}
WORKDIR ${HOME}

RUN sudo rosdep init
RUN sudo apt-get install python-rosinstall -y
RUN sudo apt-get install -q -y ros-kinetic-rqt*

# initialize-ros-permission.sh
RUN rosdep update 
RUN sudo rosdep fix-permissions 
RUN echo HOME=${HOME}

VOLUME /docker_share
RUN ln -s /docker_share $HOME

# visual studio code
RUN sudo apt-get install -y libnss3 libxkbfile1 libsecret-1-0
RUN wget -O $HOME/code_1.33.1-1554971066_amd64.deb https://go.microsoft.com/fwlink/?LinkID=760868
RUN sudo dpkg -i $HOME/code_1.33.1-1554971066_amd64.deb && rm -f $HOME/code_1.33.1-1554971066_amd64.deb 
#RUN code --install-extension platformio.platformio-ide --force
#RUN code --install-extension ms-vscode.cpptools --force
ADD docker_home/initial-vcode.sh $HOME/.initial-vcode.sh
ADD docker_home/run-vcode.sh $HOME/


# initros-kinetic-rqt catkin workspace
#RUN source /opt/ros/kinetic/setup.bash
#RUN mkdir -p $HOME/docker_share/catkin_ws/src && cd $HOME/docker_share/catkin_ws/src && catkin_init_workspace
#RUN cd $HOME/docker_share/catkin_ws && catkin_make
# you should run it once 
ADD docker_home/initial-workspace.sh $HOME/.initial-workspace.sh

# override ~/.platformio
# moved to run-vcode.sh
#RUN echo "export PLATFORMIO_HOME_DIR=${HOME}/docker_share/code/.platformio" >> $HOME/.bashrc

# ros env
RUN echo "source /opt/ros/kinetic/setup.bash" >> $HOME/.bashrc
RUN echo "source \$HOME/docker_share/catkin_ws/devel/setup.bash" >> $HOME/.bashrc
#RUN echo "export ROS_HOSTNAME=localhost" >> $HOME/.bashrc
#RUN echo "export ROS_MASTER_URI=http://localhost:11311" >> $HOME/.bashrc
RUN echo "alias cw='cd ~/docker_share/catkin_ws'" >> $HOME/.bashrc
RUN echo "alias cs='cd ~/docker_share/catkin_ws/src'" >> $HOME/.bashrc
RUN echo "alias cm='cd ~/docker_share/catkin_ws && catkin_make'" >> $HOME/.bashrc

# VOLUME
# home folder(/home/travis)를 volume으로 만들고 container가 생성되면 
# 생성된 내용을 복사한다.
# This Dockerfile results in an image that causes docker run to create a new mount point at /myvol and copy the greeting file into the newly created volume.
#VOLUME /home/${UNAME}


ADD ros_entrypoint2.sh /

