#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ML SungKim 강의, placeholder의 개념과 사용법을 알려준 코드
                               약간 c#의 object 타입처럼 우선 변수를 선언해주는 코드 같다
'''

import tensorflow as tf

xdata = [1,2,3]
ydata = [1,2,3]

W = tf.Variable(tf.random_uniform([1],-1.0,1.0))
b = tf.Variable(tf.random_uniform([1],-1.0,1.0))

X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

hypothesis = W * X + b

cost = tf.reduce_mean(tf.square(hypothesis - Y))

a = tf.Variable(0.1)
optimizer = tf.train.GradientDescentOptimizer(a)
train = optimizer.minimize(cost)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

for step in xrange(2001):
	sess.run(train, feed_dict={X:xdata, Y:ydata})
	if step % 20 == 0:
		print step, sess.run(cost, feed_dict={X:xdata, Y:ydata}) , sess.run(W), sess.run(b)

print sess.run(hypothesis, feed_dict={X:5})
print sess.run(hypothesis, feed_dict={X:2.5})
