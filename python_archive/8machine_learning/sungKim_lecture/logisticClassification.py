#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ML SungKim 강의, numpy로 파일을 불러와 Logistic Classifier를 구현해본 코드
                               공부시간, 수업참여율의 데이터를 사용해 학생의 다음 시험 당락여부를 예측해보는 코드
'''

import tensorflow as tf
import numpy as np

xy = np.loadtxt('train2.txt', unpack = True, dtype = 'float32')

xdata = xy[0:-1]
ydata = xy[-1]

X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

W = tf.Variable(tf.random_uniform([1, len(xdata)], -1.0, 1.0))

h = tf.matmul(W,X)
hypothesis = tf.div(1., 1.+tf.exp(-h))

cost = -tf.reduce_mean(Y*tf.log(hypothesis) + (1-Y)*tf.log(1-hypothesis))

a = tf.Variable(0.1)
optimizer = tf.train.GradientDescentOptimizer(a)
train = optimizer.minimize(cost)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

for step in xrange(2001):
	sess.run(train, feed_dict={X:xdata, Y:ydata})
	if step % 20 == 0:
		print step, sess.run(cost, feed_dict={X:xdata,Y:ydata}), sess.run(W)

print '-----------------------------------------------'
# study_hour attendance
print sess.run(hypothesis, feed_dict={X:[[1],[2],[2]]}) > 0.5
print sess.run(hypothesis, feed_dict={X:[[1],[5],[5]]}) > 0.5

print sess.run(hypothesis, feed_dict={X:[[1,1],[4,3],[3,5]]}) > 0.5
