#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ML SungKim 강의, Cost Funtion의 최소값을 그래프를 통해 알아보는 코드
'''
import tensorflow as tf
import matplotlib.pyplot as plt

X = [1.,2.,3.]
Y = [1.,2.,3.]
m = n_samples = len(X)

W = tf.placeholder(tf.float32)

hypothesis = tf.multiply(X,W)

cost = tf.reduce_sum(tf.pow(hypothesis - Y, 2))/(m)
init = tf.global_variables_initializer()

Wval = []
costval = []

sess = tf.Session()
sess.run(init)

for i  in range(-30,50):
	print i*0.1, sess.run(cost, feed_dict={W: i*0.1})
	Wval.append(i*0.1)
	costval.append(sess.run(cost, feed_dict={W: i*0.1}))

plt.plot(Wval, costval , 'ro')
plt.ylabel('Cost')
plt.xlabel('W')
plt.show()
