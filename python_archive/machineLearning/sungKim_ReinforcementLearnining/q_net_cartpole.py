#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> SungKim RL lab6-2, CartPole 예제를 Q Network를 사용해 돌려보는 코드
                                  결과가 Random으로 CartPole을 하는 것과 비슷하게 좋지않다
'''
import numpy as np
import tensorflow as tf
import gym

env = gym.make('CartPole-v0')

learning_rate = 1e-1
input_size = env.observation_space.shape[0]
output_size = env.action_space.n

X = tf.placeholder(tf.float32, [None, input_size], name="input_x")  # [1x4]
W1 = tf.get_variable("W1", shape=[input_size, output_size],         # [4x2]
        initializer=tf.contrib.layers.xavier_initializer())

Qpred = tf.matmul(X, W1)  # [1x2]

Y = tf.placeholder(shape=[None, output_size], dtype=tf.float32)

loss = tf.reduce_sum(tf.square(Y - Qpred))

train = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)

num_episodes = 2000
dis = 0.9
rList = []

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

for i in range(num_episodes):
    eps = 1. / ((i/50) + 10)
    rAll = 0
    step_count = 0
    s = env.reset()
    done = False

    while not done:
        step_count += 1
        x = np.reshape(s, [1, input_size])

        Qs = sess.run(Qpred, feed_dict={X:x})

        if np.random.rand(1) < eps:
            a = env.action_space.sample()
        else:
            a = np.argmax(Qs)

        s1, reward, done, _ = env.step(a)
        if done:
            Qs[0, a] = -100   # 넘어지는 순간 -100의 Reward를 준다
        else:
            x1 = np.reshape(s1, [1, input_size])
            Qs1 = sess.run(Qpred, feed_dict={X:x1})
            Qs[0, a] = reward + dis*np.max(Qs1)

        sess.run(train, feed_dict={X:x, Y:Qs})
        s = s1

    rList.append(step_count)
    print("Episode: {}  steps:  {}".format(i, step_count))
    
    # if last 10's avg steps are 500, it's good enough
    if len(rList) > 10 and np.mean(rList[-10:]) > 500:
        break


observation = env.reset()
reward_sum = 0

while True:
    env.render()

    x = np.reshape(observation, [1, input_size])
    Qs = sess.run(Qpred, feed_dict={X:x})
    a = np.argmax(Qs)

    observation, reward, done, _ = env.step(a)
    reward_sum += reward
    if done:
        print("Total Socre: {}".format(reward_sum))
        break



