#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==>
'''
import tensorflow as tf

# 변수를 받을 a, b를 설정합니다
a = tf.placeholder(tf.int16)
b = tf.placeholder(tf.int16)

# 더하는 기능과 곱하는 기능을 사용합니다.
add = tf.add(a,b)
mul = tf.multiply(a,b)

with tf.Session() as sess:
	print "add is : %i " % sess.run(add, feed_dict={a:2, b:3})
	print "mul is : %i " % sess.run(mul, feed_dict={a:2, b:3})

