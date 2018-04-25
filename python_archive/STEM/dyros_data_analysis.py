import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


#START============================================
# ed: dyros_#.txt 파일을 불러오는 코드
dyros_np = np.loadtxt('./dyros_002_1.txt', delimiter=',')
dyros_pd = pd.DataFrame(dyros_np)
#END==============================================


#START============================================
# ed: dyros_np 변수에 value 별로 갯수를 세주는 코드
unique, counts = np.unique(dyros_np, return_counts=True)
dict(zip(unique, counts))
#END==============================================



#START============================================
# ed: dyros_#.txt 파일에서 [0,0,0,0,0,0,0,0]의 비율을 검사하는 코드
# Label Count : 8714
# 모든 Pointcloud   선택했다
dyros_np = np.loadtxt('./dyros_002_15.txt', delimiter=',')
dyros_pd = pd.DataFrame(dyros_np)

unique, counts = np.unique(dyros_np[:,:3], return_counts=True)
(counts.sum()-counts.max()) / float(counts.sum())
#END==============================================



