#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ML SungKim 강의,	Linear Regression을 이용해 XOR 연산을 구현해본 코드
                                Linear Regression보다 NN 방식의 Accuracy가 더 높다
'''

import tensorflow as tf
import numpy as np


xy = np.loadtxt('train4.txt',unpack = True)
xdata = xy[0:-1]
ydata = xy[-1]

X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

W = tf.Variable(tf.random_uniform([1, len(xdata)], -1.0, 1.0))

h = tf.matmul(W, X)
hypothesis = tf.div(1., 1. + tf.exp(-h))
cost = -tf.reduce_mean(Y*tf.log(hypothesis) + (1-Y)*tf.log(1-hypothesis))

a = tf.Variable(0.01)
optimizer = tf.train.GradientDescentOptimizer(a)
train = optimizer.minimize(cost)

init = tf.global_variables_initializer()
sess = tf.Session()

with tf.Session() as sess:
	sess.run(init)
	for step in range(20001):
		sess.run(train, feed_dict={X:xdata, Y:ydata})
		if step % 1000 == 0:
			print(
				step,
				sess.run(cost,feed_dict={X:xdata,Y:ydata}),
				sess.run(W)
			)

	correct_prediction = tf.equal(tf.floor(hypothesis+0.5),Y)
	accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

	print sess.run([hypothesis, tf.floor(hypothesis+0.5), correct_prediction, accuracy], feed_dict={X:xdata, Y:ydata})
	print "Accuracy: ", accuracy.eval({X:xdata, Y:ydata})
