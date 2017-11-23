#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ML SungKim 강의, Gradient Descent Algorithm을 사용해 최소의 Cost Function을 구해본 코드
                                W -> 1
                                b -> 0
'''

import tensorflow as tf

xdata = [1,2,3]
ydata = [1,2,3]

W = tf.Variable(tf.random_uniform([1],-1.0,1.0))
b = tf.Variable(tf.random_uniform([1],-1.0,1.0))

hypothesis = W * xdata + b

cost = tf.reduce_mean(tf.square(hypothesis - ydata))

a = tf.Variable(0.1)
optimizer = tf.train.GradientDescentOptimizer(a)
train = optimizer.minimize(cost)

init = tf.global_variables_initializer()

sess = tf.Session()
sess.run(init)

for step in xrange(2001):
	sess.run(train)
	if step % 20 == 0:
		print step, sess.run(cost), sess.run(W), sess.run(b)
