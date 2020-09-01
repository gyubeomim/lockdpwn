export STEREODSO_PATH=${HOME}/gitrepo/stereo-dso-sandbox

cd ${STEREODSO_PATH}/build && make -j6

case $1 in
    00)
        seq=$1

        ${STEREODSO_PATH}/build/bin/dso_dataset \
                         files=${HOME}/dataset/kitti/data_odometry/sequences/${seq} \
                         calib=${HOME}/catkin_ws/config/dso/camera_kitti_left.txt \
                         calib_right=${HOME}/catkin_ws/config/dso/camera_kitti_right.txt \
                         vocab=${HOME}/vocabulary/ORBvoc.bin \
                         gtPath=${HOME}/dataset/kitti/data_odometry/poses/00.txt \
                         preset=0 \
                         speed=1 \
                         mode=1 \
                         openLoop=1
        ;;
esac
# gamma=${HOME}/catkin_ws/config/dso/pcalib.txt \
    # vignette=${HOME}/catkin_ws/config/dso/vignette.png \
    # set speed=1 to play with real-time. otherwise, it plays as fast as possible.
