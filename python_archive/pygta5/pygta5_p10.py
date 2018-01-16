#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.10 코드를 따라해본 코드
                
                최종적으로 한번 더 데이터전처리를 한 코드 
                차량의 데이터에서 W(전진)이 과도하게 많으므로 전진데이터의 갯수를 줄였다
'''
import numpy as np
import pandas as pd
from collections import Counter
from random import shuffle
import cv2

train_data = np.load('training_data.npy')

# 각각 키보드데이터의 개수를 확인한다
df = pd.DataFrame(train_data)
print(Counter(df[1].apply(str)))

lefts = []
rights = []
forwards = []

# 데이터의 순서를 랜덤으로 섞는다
shuffle(train_data)

# 데이터를 다시 가공한다. 각각 [영상, 조작키]로 데이터를 가공한다
for data in train_data:
    img = data[0]
    choice = data[1]

    if choice == [1,0,0]:
        lefts.append([img, choice])
    elif choice == [0,1,0]:
        forwards.append([img, choice])
    elif choice == [0,0,1]:
        rights.append([img, choice])
    else:
        print('no matches!')


# 보통 전진(forwards)에 관한 데이터가 많으므로 학습할 때 전진쪽으로 치우쳐서 학습되는 경우가 많다
# 이를 방지하기 위해 각각 케이스별로 같은 데이터 크기를 만들어주는 코드
forwards = forwards[:len(lefts)][:len(rights)]
lefts = lefts[:len(forwards)]
rights = rights[:len(rights)]


# 최종적으로 데이터를 합친다
final_data = forwards + lefts + rights
shuffle(final_data)
print('[*] final_data\'s length is : ' + str(len(final_data)))
np.save('training_data_v2.npy', final_data)


# 학습데이터를 확인할 경우에 주석을 해제합니다
'''
for data in train_data:
    img = data[0]
    choice = data[1]

    cv2.imshow('test', img)
    print(choice)

    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break
'''




