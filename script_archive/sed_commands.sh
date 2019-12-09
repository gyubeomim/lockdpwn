- find ./ -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/test_ws/catkin_ws/g'


- find /home/user/catkin_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/catkin_ws_kinetic/catkin_ws/g'
    - gitrepo/ims/ROS/catkin_ws_kinetic  ==> catkin_ws



- find /home/user/catkin_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/catkin_ws_indigo/catkin_ws/g'
    - gitrepo/ims/ROS/catkin_ws_indigo   ==> catkin_ws



- find /home/user/cartographer_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/cartographer_ws_kinetic/cartographer_ws/g'
    - gitrepo/ims/ROS/cartographer_ws_kinetic ==> cartographer_ws



- find /home/user/gitrepo/ims/ROS/cartographer_ws_kinetic -type f -print0 | xargs -0 sed -i 's/user\/cartographer_ws/user\/gitrepo\/ims\/ROS\/cartographer_ws_kinetic/g'
    - user/cartographer_ws ==> user/gitrepo/ims/ROS/cartographer_ws_kinetic


- find /home/user/gitrepo/ims/ROS/catkin_ws -type f -print0 | xargs -0 sed -i 's/lockdpwn/ims/'
    - lockdpwn --> ims


- find /home/user/catkin_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/lockdpwn\/ROS\///g'
    - gitrepo/lockdpwn/ROS/ --> ''


- find /home/user/gitrepo/ims/ROS/catkin_ws -type f -print0 | xargs -0 sed -i 's/dyros_simualtor/dyros_simulator/'
    - dyros_simualtor --> dyros_simulator



- find /home/user/gitrepo/ims/ROS/catkin_ws -type f -print0 | xargs -0 sed -i 's/dbw_mkz_description/dyros_simulator/'
    - dbw_mkz_description --> dyros_simulator



find ./ -type f -print0 | xargs -0 sed -i 's/home\/user/media\/dyros-data/g'

