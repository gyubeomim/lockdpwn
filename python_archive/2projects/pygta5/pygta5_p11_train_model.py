#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.11 코드를 따라해본 코드

                전처리한 데이터를 alexnet_v2에 넣어서 학습을 한 코드
'''
import numpy as np
from alexnet import alexnet

# 기본 설정 
WIDTH = 80
HEIGHT = 60
LR = 1e-3      # Learning Rate
EPOCHS = 8     

# 모델의 이름을 아래와 같이 Learning_Rate, 이름, Epochs 정보를 추가해서 알아보기 쉽게 한다
MODEL_NAME = 'pygta5-car-{}-{}-{}-epoch.model'.format(LR, 'alexnetv2', EPOCHS)


# alexnet 객체를 생성한다
model = alexnet(WIDTH, HEIGHT, LR)

# 학습데이터를 불러온 다음
train_data = np.load('training_data_v2.npy')

# 원하는 크기로 Test, Train 데이터를 나누고
train = train_data[:-100]
test = train_data[-100:]


# 데이터(영상)와 정답(키보드데이터)를 분리한다
X = np.array([i[0] for i in train]).reshape(-1, WIDTH, HEIGHT, 1)
Y = [i[1] for i in train]

test_X = np.array([i[0] for i in test]).reshape(-1, WIDTH, HEIGHT, 1)
test_Y = [i[1] for i in test]


# 학습을 시작한다
model.fit({'input':X}, {'targets':Y}, n_epoch=EPOCHS, 
        validation_set=({'input':test_X}, {'targets':test_Y}), 
        snapshot_step=100, show_metric=True, run_id=MODEL_NAME)


# 파이썬스크립트가 있는 경로에 log 폴더를 만들고 
# 학습을 하면서 새로운 cmd창에 아래 명령어를 치면 실시간으로 loss, accuracy 그래프를 확인할 수 있다
# tensorboard --logdir=foo:E:/gitrepo/lockdpwn/python_archive/pygta5/log


# 학습이 끝나면 모델을 저장한다
model.save(MODEL_NAME)






