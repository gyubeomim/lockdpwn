#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 비주얼컴퓨팅, Deep MNIST로 Convolution, fully connected, dropout등의 기법을 통해 여러 층의 신경망을 만들어본 코드
'''
# %matplotlib inline # ipython 전용 코드
import matplotlib.pyplot as plt
import tensorflow as tf
import numpy as np
from tensorflow.examples.tutorials.mnist import input_data


# 데이터를 불러와서 mnist 변수에 담는다
data_dir = './MNIST_data/'
mnist = input_data.read_data_sets(data_dir, one_hot=True, validation_size=5000)


# None 은 내가 얼만큼의 데이터를 넣을지 안 정했을 때 사용한다
x_input = tf.placeholder(tf.float32, [None, 784])
y_input = tf.placeholder(tf.float32, [None, 10])


# 가중치를 초기화하는 함수 (정규분포 stddev=0.1로 초기화한다)
def weight_variable(shape):
	initial = tf.truncated_normal(shape, stddev=0.1)
	return tf.Variable(initial)


# 바이어스를 초기화하는 함수 (0.1로 초기화한다)
def bias_variable(shape):
	initial = tf.constant(0.1, shape=shape)
	return tf.Variable(initial)


# 컨벌루션을 실행하는 함수
# padding = 'same' 입력과 출력의 이미지 크기가 같도록 해준다
def conv2d(x, W):
	return tf.nn.conv2d(x, W, strides=[1,1,1,1], padding='SAME')


# max pooling을 실행하는 함수
def max_pool_2x2(x):
	return tf.nn.max_pool(x, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')



# 1st conv layer ----------------------
W_conv1 = weight_variable([5,5,1,32])
b_conv1 = bias_variable([32])

# -1 : 아직 디멘젼이 결정되지 않았다
# x_input은 784x1인데 28x28x1로 행렬을 다시 만들어준다
x_image = tf.reshape(x_input, [-1,28,28,1])

# y = x*w + b에 ReLU를 적용한다
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)





# 2nd conv layer -----------------------
W_conv2 = weight_variable([5,5,32,64])
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)







# 1st fully connected layer -----------------------
W_fc1 = weight_variable([7*7*64, 1024])
b_fc1 = bias_variable([1024])

h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
# 위 연산으로 1024x1의 벡터가 생성된다



# Dropout ------------------------
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)




# 2nd fully connected layer --------------
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])
y_conv = tf.matmul(h_fc1_drop, W_fc2) + b_fc2




# Cross Entropy를 정의한다
cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_input, logits=y_conv))


# Adam Optimizer 알고리즘을 사용해서 cross_entropy를 최소화한다. 학습율은 1e-4로 한다
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

# 세션을 초기화한다
sess = tf.InteractiveSession()
sess.run(tf.global_variables_initializer())

# 실제 정답과 예측값이 얼마나 일치하는지를 판단하는 accuray 변수를 정의한다
corerct_predition = tf.equal(tf.argmax(y_conv, 1) , tf.argmax(y_input, 1))
accuracy = tf.reduce_mean(tf.cast(corerct_predition, tf.float32))


for i in range(2000):
	# [image[50], label[50]]를 6만개의 기존 데이터에서 랜덤으로 한 묶음으로 처리한다음 이것을 학습한다
	batch = mnist.train.next_batch(50)
	# 100번 돌릴 때마다 결과를 확인한다
	if i%100 == 0:
		train_accuracy = accuracy.eval(feed_dict={x_input:batch[0], y_input:batch[1], keep_prob:1.0})

		print('step', i , 'training_accuracy', train_accuracy)
	train_step.run(feed_dict={x_input:batch[0],y_input:batch[1], keep_prob:0.5})



# 전부 학습이 끝나면 테스트 데이터를 넣는다
test_accuracy = accuracy.eval(feed_dict={x_input: mnist.test.images, y_input: mnist.test.labels, keep_prob: 1.0})
print('test accuracy', test_accuracy)
