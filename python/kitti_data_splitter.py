#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
   #+DESCRITION:  kitti dataset을 다루기 위한 몇몇 Python 함수들

   #+DATE:        2018-08-30-목
   #+AUTHOR:      Edward Im (gyurse@gmail.com)
'''
import os
from os import listdir
from os.path import isfile, join
import shutil

# ed: MV3D, VoxelNet 같이 KITTI 데이터셋의 training 폴더를 training/validation으로 train.txt, val.txt 파일에 따라 나눠주는 코드
def split_training_validation():
  DATA_DIR = "/media/dyros-data/datasets/kitti/voxelnet_data/training/"
  val_txt = open(DATA_DIR + "/val.txt", 'r')

  for line in val_txt:
    line = line.split('\n')[0]
    fname = DATA_DIR + "velodyne/" + line + ".bin"
    # print(fname)    # DEBUG

    if os.path.isfile(fname):
      shutil.move(fname, "/media/dyros-data/datasets/kitti/voxelnet_data/validation/velodyne/")


# ed: 1.bin, 2.bin 같은 파일을 000001.bin, 000002.bin 으로 변경해주는 함수 for VoxelNet
def rename_cropped_velodyne():
  DATA_DIR = "/media/dyros-data/datasets/kitti/voxelnet_data/training/velodyne"
  datanames= [f for f in listdir(DATA_DIR) if isfile(join(DATA_DIR, f))]
  fnames = []
  for i in range(0, len(datanames)):
    fnames.append(datanames[i].replace('.bin',''))

  for i in range(0, len(fnames)):
    zfill_fname = fnames[i].zfill(6)
    zfill_fname = zfill_fname + ".bin"
    DESTINATION = os.path.join(DATA_DIR, datanames[i])
    shutil.move(DESTINATION, "/media/dyros-data/datasets/kitti/voxelnet_data/trainingvelodyne/" + zfill_fname)


if __name__ == '__main__':
  split_training_validation()
  # rename_cropped_velodyne()
