<<<<<<< HEAD
find ./ -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/test_ws/catkin_ws/g'
=======
- find /home/dyros-vehicle/catkin_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/catkin_ws_kinetic/catkin_ws/g'
    - gitrepo/ims/ROS/catkin_ws_kinetic  ==> catkin_ws



- find /home/dyros-vehicle/catkin_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/catkin_ws_indigo/catkin_ws/g'
    - gitrepo/ims/ROS/catkin_ws_indigo   ==> catkin_ws



- find /home/dyros-vehicle/cartographer_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/ims\/ROS\/cartographer_ws_kinetic/cartographer_ws/g'
    - gitrepo/ims/ROS/cartographer_ws_kinetic ==> cartographer_ws



- find /home/dyros-vehicle/gitrepo/ims/ROS/cartographer_ws_kinetic -type f -print0 | xargs -0 sed -i 's/dyros-vehicle\/cartographer_ws/dyros-vehicle\/gitrepo\/ims\/ROS\/cartographer_ws_kinetic/g'
    - dyros-vehicle/cartographer_ws ==> dyros-vehicle/gitrepo/ims/ROS/cartographer_ws_kinetic


- find /home/dyros-vehicle/gitrepo/ims/ROS/catkin_ws -type f -print0 | xargs -0 sed -i 's/lockdpwn/ims/'
    - lockdpwn --> ims


- find /home/dyros-vehicle/catkin_ws -type f -print0 | xargs -0 sed -i 's/gitrepo\/lockdpwn\/ROS\///g'
    - gitrepo/lockdpwn/ROS/ --> ''


- find /home/dyros-vehicle/gitrepo/ims/ROS/catkin_ws -type f -print0 | xargs -0 sed -i 's/dyros_simualtor/dyros_simulator/'
    - dyros_simualtor --> dyros_simulator



- find /home/dyros-vehicle/gitrepo/ims/ROS/catkin_ws -type f -print0 | xargs -0 sed -i 's/dbw_mkz_description/dyros_simulator/'
    - dbw_mkz_description --> dyros_simulator
>>>>>>> ab9426d2ebea3e8cc41f02098ab43b40d40c33e9
