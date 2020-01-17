export LDSO_HOME=${HOME}/gitrepo/LDSO

${LDSO_HOME}/bin/run_dso_kitti \
					preset=0 \
					files=/media/data/dataset/kitti/data_odometry/sequences/00/ \
					calib=${LDSO_HOME}/examples/Kitti/Kitti00-02.txt
