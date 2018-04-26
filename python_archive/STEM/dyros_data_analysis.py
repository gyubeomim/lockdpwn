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
# ed: dyros_#.txt 파일에서 [0,0,0,0,0,0,0,0]이 아닌 데이터만 따로 저장하는 코드
pop_list = []
for i in range(dyros_np.shape[0]):
    if dyros_np[i].any() == np.zeros(8).any():
        pop_list.append(i)
dyros_np2 = np.delete(dyros_np, pop_list, 0)
np.savetxt('nozero_dyros_1.txt', dyros_np2, fmt='.2f')
#END==============================================



#START============================================
# ed: dyros_#.txt 데이터에서 xyzi만 있는 데이터, rgb만 있는데이터, NULL 데이터는 몇개가 있는지 등등 확인하는 코드
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

dyros_np = np.loadtxt('./dyros_002_15.txt', delimiter=',')
dyros_pd = pd.DataFrame(dyros_np)

xyzi_only = np.empty(0)
rgb_only = np.empty(0)
label_count = np.empty(0)
null_only = np.empty(0)    # null_only : [0,0,0,0,0,0,0,1]
all_zero = 0               # all_zero  : [0,0,0,0,0,0,0,0]

for i in range(dyros_np.shape[0]):
    if dyros_np[i][0:3].any() and not dyros_np[i][4:7].any():
        xyzi_only = np.append(xyzi_only, dyros_np[i]).reshape(-1,8)
    elif not dyros_np[i][0:3].any() and dyros_np[i][4:7].any():
        rgb_only = np.append(rgb_only, dyros_np[i]).reshape(-1,8)
    elif not dyros_np[i][0:7].any() and dyros_np[i][7].any():
        null_only = np.append(null_only, dyros_np[i]).reshape(-1,8)
    if dyros_np[i][7] == 1:
        label_count = np.append(label_count, dyros_np[i]).reshape(-1,8)
    if not dyros_np[i].any():
        all_zero += 1
print('\n[+] length : {:^18} \n[+] xyzi_only : {:^10} \n[+] rgb_only : {:^10} \n[+] null_only : {:^10} \n[+] label count : {:^8} \n[+] all zero : {:>10}'.format(dyros_np.shape[0],xyzi_only.shape[0],rgb_only.shape[0],null_only.shape[0], label_count.shape[0], all_zero))
#END==============================================



#START============================================
# ed: dyros_#.txt 파일에서 '0' 값의 비율을 검사하는 코드
# Label Count : 8714
# 모든 Pointcloud   선택했다
dyros_np = np.loadtxt('./dyros_002_15.txt', delimiter=',')
dyros_pd = pd.DataFrame(dyros_np)

unique, counts = np.unique(dyros_np[:,:3], return_counts=True)
(counts.sum()-counts.max()) / float(counts.sum())
#END==============================================


#START============================================

#END==============================================
