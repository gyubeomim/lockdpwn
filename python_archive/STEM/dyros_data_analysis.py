import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


#START============================================
# ed: dyros_#.txt 파일 분석 코드
dyros_np = np.loadtxt('./dyros_002_1.txt', delimiter=',')
dyros_pd = pd.DataFrame(dyros_np)
#END==============================================


#START============================================
# ed: pred_cls 변수에 value 별로 갯수를 세주는 코드
unique, counts = np.unique(pred_cls, return_counts=True)
dict(zip(unique, counts))
#END==============================================
