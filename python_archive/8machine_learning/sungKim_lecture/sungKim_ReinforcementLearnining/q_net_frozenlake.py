#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> SungKim RL lab6-1, FrozenLake 게임을 Q network를 사용해서 학습하는 코드
'''
import gym
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

env = gym.make("FrozenLake-v0")

input_size = env.observation_space.n
output_size = env.action_space.n
learning_rate = 0.1

X = tf.placeholder(shape=[1,input_size], dtype=tf.float32)
W = tf.Variable(tf.random_uniform([input_size, output_size], 0, 0.01))

Qpred = tf.matmul(X, W)
Y = tf.placeholder(shape=[1, output_size], dtype=tf.float32)

loss = tf.reduce_sum(tf.square(Y - Qpred))

train = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss)

dis = 0.99
num_episode = 2000

rList = []
init = tf.global_variables_initializer()

def one_hot(tot_len, x):
    return np.identity(tot_len)[x:x+1]

with tf.Session() as sess:
    sess.run(init)
    for i in range(num_episode):
        s = env.reset()
        eps = 1. / ((i/50) + 10)
        rAll = 0
        done = False
        local_loss = []

        while not done:
            Qs = sess.run(Qpred, feed_dict={X: one_hot(16,s)})

            if np.random.rand(1) < eps: # epsilon Greedy 
                a = env.action_space.sample()
            else:
                a = np.argmax(Qs)

            s1, reward, done, _ = env.step(a)

            if done:
                Qs[0,a] = reward
            else:
                Qs1 = sess.run(Qpred, feed_dict={X:one_hot(16,s1)})
                Qs[0,a] = reward + dis*np.max(Qs1)


            sess.run(train, feed_dict={X:one_hot(16,s), Y:Qs})
            rAll += reward
            s = s1

        rList.append(rAll)
        
print("Percent of successful episodes: " + str(sum(rList)/num_episode) + "%")
plt.bar(range(len(rList)), rList, color="blue")
plt.show()



            










