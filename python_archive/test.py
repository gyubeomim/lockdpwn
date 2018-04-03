#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
    python ==> dyros, [x,y,z,intensity] 필드를 가지고 있는 veloydne_point cloud 데이터를 numpy, pandas로 가공해본
'''

import numpy as np
import pandas as pd


data = open('velodyne_points.dat', 'r').read().split('\n')

# ed: create (0,0,0,0)
data_np = np.zeros(4)

for i in range(0, 10000):
    data_np = np.vstack((data_np, data[i].split(', ')))

    if(i % 2000 == 0):
        print(i)


# ed: remove first zeros (0,0,0,0)
data_np = data_np[1:len(data_np)].astype(np.float)

data_pd = pd.DataFrame(data=data_np)


data_pd.info()
data_pd.hist()
data_pd.sum()
data_pd.describe()


#-------------------------------------------------------------

data2 = open('Grid_JW_1.txt', 'r').read().split('\n')

# ed: create (0,0,0,0)
data_np2 = np.zeros(8)

for i in range(0, 10000):
    data_np2 = np.vstack((data_np2, data2[i].split(', ')))

    if(i % 2000 == 0):
        print(i)


# ed: remove first zeros (0,0,0,0)
data_np2 = data_np2[1:len(data_np2)].astype(np.float)

data_pd2 = pd.DataFrame(data=data_np2)


data_pd2.info()
data_pd2.hist()
data_pd2.sum()
data_pd2.describe()
