#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> keras book, 케라스 사용법을 알기위해 테스트해 본 코드 
'''
from keras.layers import Dense
from keras.models import Sequential

x_train = []
y_train = []

model = Sequential()
model.add(Dense(12, input_dim=5, activation='sigmoid'))
model.add(Dense(30, activation='sigmoid'))
model.add(Dense(1,  activation='sigmoid'))
model.compile(loss='mse', optimizer='RMSProp')


# model의 세부내용을 볼 때 사용하는 코드
model.summary()


model.fit(x_train, y_train, batch_size=32, epoch=1)


