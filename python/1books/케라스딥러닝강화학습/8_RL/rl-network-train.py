#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 케라스딥러닝강화학습 p351, DQN(3-Conv, 2-FC) 모델 + 경험리플레이를 사용해서 떨어지는 블록을 받는 Agent를 강화학습시키는 코드
'''
from __future__ import division, print_function
from keras.models import Sequential
from keras.layers.core import Activation, Dense, Flatten
from keras.layers.convolutional import Conv2D
from keras.optimizers import Adam
from scipy.misc import imresize
import collections
import numpy as np
import os
import keras.backend.tensorflow_backend as K

# custom packages------
import wrapped_game


############################# main ###############################
# initialize parameters
DATA_DIR = "./data"
NUM_ACTIONS = 3           # number of valid actions (left, stay, right)
GAMMA = 0.99              # decay rate of past observations
INITIAL_EPSILON = 0.1     # starting value of epsilon
FINAL_EPSILON = 0.0001    # final value of epsilon
MEMORY_SIZE = 50000       # number of previous transitions to remember
NUM_EPOCHS_OBSERVE = 100
NUM_EPOCHS_TRAIN = 2000

BATCH_SIZE = 32
NUM_EPOCHS = NUM_EPOCHS_OBSERVE + NUM_EPOCHS_TRAIN



# 이미지로부터 state를 반환하는 함수인듯
def preprocess_images(images):
    if images.shape[0] < 4:
        # 단일 이미지
        x_t = images[0]
        x_t = imresize(x_t, (80,80))
        x_t = x_t.astype("float")
        x_t /= 255.0

        s_t = np.stack((x_t, x_t, x_t, x_t), axis=2)

    else:
        # 4장의 이미지
        xt_list = []

        for i in range(images.shape[0]) :
            x_t = imresize(images[i], (80,80))
            x_t = x_t.astype("float")
            x_t /= 255.0

            xt_list.append(x_t)

        s_t = np.stack((xt_list[0], xt_list[1], xt_list[2], xt_list[3]), axis=2)

    s_t = np.expand_dims(s_t, axis=0)
    return s_t



# 경험리플레이 리스트에서 X, Y를 추출하는 함수인드 
def get_next_batch(experience, model, num_actions, gamma, batch_size):
    batch_indices = np.random.randint(low=0, high=len(experience), size=batch_size)

    batch = [experience[i] for i in batch_indices]
    X = np.zeros((batch_size, 80,80,4))
    Y = np.zeros((batch_size, num_actions))

    for i in  range(len(batch)):
        s_t, a_t, r_t, s_tp1, game_over = batch[i]
        X[i] = s_t
        Y[i] = model.predict(s_t)[0]

        Q_sa = np.max(model.predict(s_tp1)[0])
    
        if game_over:
            Y[i, a_t] = r_t
        else:
            Y[i, a_t] = r_t + gamma * Q_sa

    return X, Y
        




# 모델, 3-Conv, 2-FC Model
with K.tf.device('/gpu:0'):
    model = Sequential()
    model.add(Conv2D(32, kernel_size=8, strides=4,
        kernel_initializer="normal",
        padding="same",
        input_shape=(80,80,4)))
    model.add(Activation("relu"))
    model.add(Conv2D(64, kernel_size=4, strides=2,
        kernel_initializer="normal",
        padding="same"))
    model.add(Activation("relu"))
    model.add(Conv2D(64, kernel_size=4, strides=2,
        kernel_initializer="normal",
        padding="same"))
    model.add(Activation("relu"))
    model.add(Flatten())
    model.add(Dense(512, kernel_initializer="normal"))
    model.add(Activation("relu"))
    model.add(Dense(3, kernel_initializer="normal"))
    # Loss Function으로 MSE를 사용한다
    model.compile(optimizer=Adam(lr=1e-6), loss="mse")



# train network
game = wrapped_game.MyWrappedGame()
experience = collections.deque(maxlen=MEMORY_SIZE)

fout = open(os.path.join(DATA_DIR, "rl-network-results.tsv"), "w")
num_games, num_wins =0, 0
epsilon = INITIAL_EPSILON


for e in  range(NUM_EPOCHS):
    loss = 0.0
    game.reset()

    a_0 = 1  # (0 = left, 1 = stay, 2 = right)
    x_t, r_0, game_over = game.step(a_0)
    s_t = preprocess_images(x_t)

    while not game_over:
        s_tm1 = s_t

        # 특정 에피소드들은 랜덤으로 행동을 취하고
        # 그 이후부터는 eps-greedy & model을 사용한다
        if e <= NUM_EPOCHS_OBSERVE:
            a_t = np.random.randint(low=0, high=NUM_ACTIONS, size=1)[0]
        else:
            if np.random.rand() <= epsilon:
                a_t = np.random.randint(low=0, high=NUM_ACTIONS, size=1)[0]
            else:
                q = model.predict(s_t)[0]
                a_t = np.argmax(q)
        

        x_t, r_t, game_over = game.step(a_t)
        s_t = preprocess_images(x_t)
        
        if r_t == 1:
            num_wins += 1

        experience.append((s_tm1, a_t, r_t, s_t, game_over))

        if e > NUM_EPOCHS_OBSERVE:
            X, Y = get_next_batch(experience, model, NUM_ACTIONS, GAMMA, BATCH_SIZE)
            loss += model.train_on_batch(X, Y)

    if epsilon > FINAL_EPSILON:
        epsilon -= (INITIAL_EPSILON - FINAL_EPSILON) / NUM_EPOCHS


    print("Epoch {:04d}/{:d} | LOSS {:.5f} | Win Count: {:d}".format(e+1, NUM_EPOCHS, loss, num_wins))
    fout.write("{:04d}\t{:.5f}\t{:d}\n".format(e+1, loss, num_wins))


    if e % 100 == 0:
        model.save(os.path.join(DATA_DIR, "rl-network.h5"), overwrite=True)

fout.close()
model.save(os.path.join(DATA_DIR, "rl-network.h5"), overwrite=True)


