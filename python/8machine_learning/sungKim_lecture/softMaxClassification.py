#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ML Sungkim 강의, Cross Entrphy를 사용해 Cost Function을 최소화하는 Softmax Classifier를 구현해보는 코드
'''

import tensorflow as tf
import numpy as np

xy = np.loadtxt('train3.txt', unpack=True, dtype = 'float32')
xdata = np.transpose(xy[0:3])
ydata = np.transpose(xy[3:])

X = tf.placeholder("float", [None, 3])
Y = tf.placeholder("float", [None, 3])

W = tf.Variable(tf.zeros([3,3]))

hypothesis = tf.nn.softmax(tf.matmul(X , W))

learning_rate = 0.001
cost = tf.reduce_mean(-tf.reduce_sum(Y*tf.log(hypothesis), reduction_indices = 1))
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

for step  in xrange(20001):
	sess.run(optimizer, feed_dict={X:xdata, Y:ydata})
	if step % 200 == 0:
		print step, sess.run(cost, feed_dict={X:xdata, Y:ydata}), sess.run(W)


a = sess.run(hypothesis, feed_dict={X:[[1,11,7]]})
print a, sess.run(tf.argmax(a,1))

b = sess.run(hypothesis, feed_dict={X:[[1,3,4]]})
print b, sess.run(tf.argmax(b,1))

c = sess.run(hypothesis, feed_dict={X:[[1,1,0]]})
print c, sess.run(tf.argmax(c,1))

all = sess.run(hypothesis, feed_dict={X:[[1,11,7],[1,3,4],[1,1,0]]})
print all, sess.run(tf.argmax(all, 1))
