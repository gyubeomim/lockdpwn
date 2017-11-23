#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> Sung Kim ML 강의, Gradient Reduce Algorithm을 적용해본 코드
'''
import tensorflow as tf

xdata = [1.,2.,3.]
ydata = [1.,2.,3.]

W = tf.Variable(tf.random_uniform([1], -10.0, 10.0))
X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

hypothesis = W * X

cost = tf.reduce_mean(tf.square(hypothesis-Y))

descent = W - tf.multiply(0.1, tf.reduce_mean(tf.multiply((tf.multiply(W,X)-Y),X)))
update = W.assign(descent)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

for step in xrange(100):
	sess.run(update, feed_dict={X:xdata, Y:ydata})
	print step, sess.run(cost, feed_dict={X:xdata,Y:ydata}), sess.run(W)
