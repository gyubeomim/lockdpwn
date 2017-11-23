#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ML SungKim 강의, Deep NN을 사용해 XOR 연산을 해본 코드
                               3층짜리 Deep 노드를 구현해서 cost가 매우 낮다
'''
import numpy as np
import tensorflow as tf

xy = np.loadtxt('xor_dataset.txt', unpack=True)

# Need to change data structure. THESE LINES ARE DIFFERNT FROM Video BUT IT MAKES THIS CODE WORKS!
xdata = np.transpose( xy[0:-1] )
ydata = np.reshape( xy[-1], (4,1) )

X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

W1 = tf.Variable(tf.random_uniform( [2,5], -1.0, 1.0))
W2 = tf.Variable(tf.random_uniform( [5,4], -1.0, 1.0))
W3 = tf.Variable(tf.random_uniform( [4,1], -1.0, 1.0))


b1 = tf.Variable(tf.zeros([5]), name="Bias1")
b2 = tf.Variable(tf.zeros([4]), name="Bias2")
b3 = tf.Variable(tf.zeros([1]), name="Bias3")

# hypothesis
L2 = tf.sigmoid(tf.matmul(X, W1) + b1)
L3 = tf.sigmoid(tf.matmul(L2, W2) + b2)
hypothesis = tf.sigmoid(tf.matmul(L3, W3) + b3)

# cost function
cost = -tf.reduce_mean(Y*tf.log(hypothesis) + (1-Y) *tf.log(1.-hypothesis))

# Minimize cost.
a = tf.Variable(0.1)
optimizer = tf.train.GradientDescentOptimizer(a)
train = optimizer.minimize(cost)

# Initializa all variables.
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

# Launch the graph
with tf.Session() as sess:
    sess.run(init)

    for step in range(20001):
        sess.run(train, feed_dict={X:xdata, Y:ydata})

        if step % 1000 == 0:
            print(
                step,
                sess.run(cost, feed_dict={X:xdata, Y:ydata}),
                sess.run(W1),
                sess.run(W2)
            )

    # Test model
    correct_prediction = tf.equal( tf.floor(hypothesis+0.5), Y)
    accuracy = tf.reduce_mean(tf.cast( correct_prediction, "float" ) )

    # Check accuracy
    print( sess.run( [hypothesis, tf.floor(hypothesis+0.5), correct_prediction, accuracy],
                   feed_dict={X:xdata, Y:ydata}) )
    print( "Accuracy:", accuracy.eval({X:xdata, Y:ydata}) )
