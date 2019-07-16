#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 비주얼컴퓨팅, 프로젝트4 얼굴 사진 55x40 데이터를 700장 사용해 단순 Neural Network를 사용함으로써 예측모델을 만들어본 코드
                            10000번 반복하니 75% 정도의 예측율을 보여준다
'''
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import scipy.misc
import scipy.io
import random

#-------------------------------------------------------------------------------
# train
train_images = []
tlabels = []

# train Image 데이터 700장을 불러온다
for num in range(1,701):
    train_images.append(scipy.misc.imread('train_image/train_'+ str(num)+'.bmp'))

# train Label 데이터를 불러온다
with open("train_label.txt") as f:
    line = [line.rstrip() for line in f]
    tlabels.append(line)

# Image 데이터와 Label 데이터를 numpy 데이터로 수정한다
train_images = np.array(train_images)
train_images = train_images.reshape(700, 2200, )

tlabels = np.array(tlabels)     # tlabels = (1,700)
tlabels = tlabels.reshape(700,1)

# train Label 데이터를 [1 x 100] 의 행렬로 표현한다
#           예를 들어 3이면 [0,0,1,0,.....,0] 과 같이 설정한다
train_labels  = np.array(np.zeros(70000).reshape(700,100))
for num in range(0,700):
    train_labels[num][int(tlabels[num][0]) - 1] = 1




#-----------------------------------------------------------------
# test
test_images = []
testlabels = []

# test Image 데이터 700장을 불러온다
for num in range(1,701):
    test_images.append(scipy.misc.imread('test_image/test_'+ str(num)+'.bmp'))

# test Label 데이터를 불러온다
with open("test_label.txt") as f:
    line = [line.rstrip() for line in f]
    testlabels.append(line)

# Image 데이터와 Label 데이터를 numpy 데이터로 수정한다
test_images = np.array(test_images)
test_images = test_images.reshape(700, 2200, )

testlabels = np.array(testlabels)     # tlabels = (1,700)
testlabels = testlabels.reshape(700,1)

# train Label 데이터를 [1 x 100] 의 행렬로 표현한다
#           예를 들어 3이면 [0,0,1,0,.....,0] 과 같이 설정한다
test_labels  = np.array(np.zeros(70000).reshape(700,100))
for num in range(0,700):
    test_labels[num][int(testlabels[num][0]) - 1] = 1


# 중요! Image 데이터들은 0~255 사이의 값이므로 255로 나눠주면서 정규화를 한다. 학습이 매우 잘된다
train_images = train_images / 255.
test_images = test_images / 255.



#------------------------------------------------------------------

_num_examples = 700
_index_in_epoch = 0
_images = train_images
_labels = train_labels
_epochs_completed = 0

# batch 연산을 수행하는 함수
# 호출될 때마다 랜덤으로 batch_size의 (Image, Label) 데이터를 반환한다
def next_batch(batch_size):
    """Return the next `batch_size` examples from this data set."""
    global _index_in_epoch
    global _images
    global _labels
    global _epochs_completed

    start = _index_in_epoch
    _index_in_epoch += batch_size

    if _index_in_epoch > _num_examples:
      # Finished epoch
      _epochs_completed += 1

      # Shuffle the data
      perm = np.arange(_num_examples)
      np.random.shuffle(perm)
      _images = _images[perm]
      _labels = _labels[perm]

      # Start next epoch
      start = 0
      _index_in_epoch = batch_size
      assert batch_size <= _num_examples

    end = _index_in_epoch
    return _images[start:end], _labels[start:end]



#-----------------------------------------------------------------
# Tensorflow 코드
#-----------------------------------------------------------------

x = tf.placeholder("float32", [None, 2200]) # mnist data image of shape 55 x 40 = 2200
y = tf.placeholder("float32", [None, 100]) 

W = tf.Variable(tf.zeros([2200,100]))
b = tf.Variable(tf.zeros([100]))
yy = tf.nn.softmax(tf.matmul(x, W) + b)


cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y, logits=yy))

learning_rate = 0.5
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

trainig_epochs = 200
display_step = 50
batch_size = 50

# training_epoch 횟수만큼 반복해서 학습한다
for epoch in range(trainig_epochs):
	avg_cost = 0.
	total_batch = int(_num_examples/batch_size)

	for i  in range(total_batch):
		batch_xs, batch_ys = next_batch(batch_size)
		#print(batch_xs[0])
		#print(batch_ys[0])
		sess.run(optimizer, feed_dict={x: batch_xs, y:batch_ys})
		avg_cost += sess.run(cost, feed_dict={x: batch_xs, y: batch_ys}) / total_batch

	if epoch % display_step == 0:
		print ("Epoch:", '%04d' % (epoch +1) , "cost=", "{:.9f}".format(avg_cost))

print ("Optimization Finished")


# 정답률을 계산한다  yy  vs  y
correct_prediction = tf.equal(tf.argmax(yy, 1), tf.argmax(y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
print(sess.run(accuracy, feed_dict= {x: test_images, y: test_labels}))



# 임의의 얼굴 하나를 출력한 다음 맞혀보는 코드 
r = random.randint(0, _num_examples -1)
print ("Label: ", sess.run(tf.argmax(test_labels[r:r+1], 1)))
print ("Prediction: ", sess.run(tf.argmax(yy, 1), {x:test_images[r:r+1]}))

plt.imshow(test_images[r:r+1].reshape(55, 40), cmap='gray', interpolation='nearest')
plt.show()

