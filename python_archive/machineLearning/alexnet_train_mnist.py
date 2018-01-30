#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> AlexNet (using keras) 을 사용해 mnist를 학습해본 코드
'''
%matplotlib inline
from __future__ import division, print_function, absolute_import

from keras.datasets import mnist
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Conv2D, MaxPooling2D
from keras.layers.normalization import BatchNormalization
from keras.optimizers import SGD
from keras.utils import np_utils
import keras.backend.tensorflow_backend as K

import matplotlib.pyplot as plt
import numpy as np



nb_classes = 10

# the data, shuffled and split between tran and test sets
(X_train, y_train), (X_test, y_test) = mnist.load_data()
print("X_train original shape", X_train.shape)
print("y_train original shape", y_train.shape)

for i in range(9):
    plt.subplot(3,3,i+1)
    plt.imshow(X_train[i], cmap='gray', interpolation='none')
    plt.title("Class {}".format(y_train[i]))

plt.show()


X_train = X_train.reshape(60000, 784)
X_test = X_test.reshape(10000, 784)
X_train = X_train.astype('float32')
X_test = X_test.astype('float32')
X_train /= 255
X_test /= 255
print("Training matrix shape", X_train.shape)
print("Testing matrix shape", X_test.shape)

Y_train = np_utils.to_categorical(y_train, nb_classes)
Y_test = np_utils.to_categorical(y_test, nb_classes)


def alexnet():
    with K.tf.device('/gpu:0'):
        model = Sequential()
        model.add(Conv2D(64, (3, 3), padding='same', input_shape=(28,28,1)))
        model.add(BatchNormalization())
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(2, 2)))

        model.add(Conv2D(128, (7, 7), padding='same'))
        model.add(BatchNormalization())
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(2, 2)))

        model.add(Conv2D(192, (3, 3), padding='same'))
        model.add(BatchNormalization())
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(2, 2)))

        model.add(Conv2D(256, (3, 3), padding='same'))
        model.add(BatchNormalization())
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(1, 1)))

        model.add(Flatten())
        model.add(Dense(4096))
        model.add(BatchNormalization())
        model.add(Activation('relu'))
        model.add(Dense(4096))
        model.add(BatchNormalization())
        model.add(Activation('relu'))
        model.add(Dense(10))
        model.add(BatchNormalization())
        model.add(Activation('softmax'))

    return model

with K.tf.device('/gpu:0'):
    model = alexnet()
    optim = SGD(lr=0.0001)
    model.compile(loss='categorical_crossentropy', optimizer=optim, metrics=['acc'])


# TRAIN MODEL-------------------------
model.fit(X_train.reshape(60000,28,28,1), Y_train, batch_size=50, epochs=20, validation_data=(X_test.reshape(10000,28,28,1),Y_test),verbose=1)


# EVALUATE MODEL---------------------
#score = model.evaluate(X_test.reshape(10000,28,28,1), Y_test, verbose=1)


# 학습된 모델에서 테스트데이터를 예측한 다음 배열로 저장한다
predicted_classes = model.predict_classes(X_test.reshape(10000,28,28,1))

# 맞은 index, 틀린 index를 저장한다
correct_indices = np.nonzero(predicted_classes == y_test)[0]
incorrect_indices = np.nonzero(predicted_classes != y_test)[0]



# 맞고 틀린 index들을 plot해주는 코드
plt.figure()
for i, correct in enumerate(correct_indices[:9]):
    plt.subplot(3,3,i+1)
    plt.imshow(X_test[correct].reshape(28,28), cmap='gray', interpolation='none')
    plt.title("Predicted {}, Class {}".format(predicted_classes[correct], y_test[correct]))
    
plt.figure()
for i, incorrect in enumerate(incorrect_indices[:9]):
    plt.subplot(3,3,i+1)
    plt.imshow(X_test[incorrect].reshape(28,28), cmap='gray', interpolation='none')
    plt.title("Predicted {}, Class {}".format(predicted_classes[incorrect], y_test[incorrect]))

plt.show()


# SAVE MODEL-------------------------
model.save("./model.h5")
