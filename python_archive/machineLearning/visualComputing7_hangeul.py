#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 비주얼컴퓨팅, 한글인식1 기존 deep MNIST 신경망에 데이터를 넣어서 학습해 본 코드
                            15000번 돌리니 76% 정도의 정확도를 보인다
'''
import h5py
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import scipy.misc
import scipy.io
import random

#-----------------------------------------------------------------
# train
train_images = []
tlabels = []

# train Image 데이터 700장을 불러온다
# train Label 데이터를 불러온다
with h5py.File('C:\\Users\\vdl\\Google Drive\\private2\\dataset_ML\\visualComputing_hangeul\\kalph_train.hf', 'r') as hf:
    train_images = np.array(hf['images'])
    tlabels = np.array(hf['labels'])


# Image 데이터와 Label 데이터를 numpy 데이터로 수정한다
train_images = train_images.reshape(19600, 2704, )


# train Label 데이터를 [1 x 100] 의 행렬로 표현한다
#           예를 들어 3이면 [0,0,1,0,.....,0] 과 같이 설정한다
train_labels  = np.array(np.zeros(274400).reshape(19600,14))
for num in range(0,19600):
    train_labels[num][int(tlabels[num]) - 1] = 1


# 10 x 10 짜리 이미지를 확인한다
rows = 10
cols = 10

# plot 창 크기를 키운 후 plot을 한다
plt.figure(figsize=(10,10))
for r in range(rows):
    for c in range(cols):
        idx = r * cols + c
        plt.subplot(rows, cols , idx +1)
        plt.imshow(train_images[idx,:,:], cmap='gray_r')
        plt.axis('off')
plt.show()


#-----------------------------------------------------------------
# test
test_images = []
testlabels = []


# train Image 데이터 700장을 불러온다
# train Label 데이터를 불러온다
with h5py.File('C:\\Users\\vdl\\Google Drive\\private2\\dataset_ML\\visualComputing_hangeul\\kalph_test.hf', 'r') as hf:
    test_images = np.array(hf['images'])
    testlabels = np.array(hf['labels'])



# Image 데이터와 Label 데이터를 numpy 데이터로 수정한다
test_images = test_images.reshape(3920, 2704, )

# train Label 데이터를 [1 x 100] 의 행렬로 표현한다
#           예를 들어 3이면 [0,0,1,0,.....,0] 과 같이 설정한다
test_labels  = np.array(np.zeros(54880).reshape(3920,14))
for num in range(0,3920):
    test_labels[num][int(testlabels[num]) - 1] = 1


# 중요! Image 데이터들은 0~255 사이의 값이므로 255로 나눠주면서 정규화를 한다. 학습이 매우 잘된다
train_images = train_images / 255.
test_images =  test_images / 255.


#-----------------------------------------------------------------

_num_examples, bins = train_images.shape
# _num_examples : 데이터 갯수

_index_in_epoch = 0   # epoch
_images = train_images  # Image 변수 
_labels = train_labels  # Label 변수
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

# None 은 내가 얼만큼의 데이터를 넣을지 안 정했을 때 사용한다
x_input = tf.placeholder(tf.float32, [None, 2704])
y_input = tf.placeholder(tf.float32, [None, 14])

# 신경망 파라미터들 y = x*w + b
W = tf.Variable(tf.zeros([2704, 14]))
b = tf.Variable(tf.zeros([14]))
y = tf.matmul(x_input , W ) + b


# softmax 알고리즘을 실행해서 y값을 최적화하고 cross_entropy를 정의한다
# softmax : 값을 0 ~ 1사이로 정규화시키는 함수 (총합은 1이 되도록 정규화하므로 확률로 변경하는 것과 같다)
y = tf.nn.softmax(y)
cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_input, logits=y))

# Gradient Descent 알고리즘을 사용해서 cross_entropy를 최소화한다. 학습율은 0.5
train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

# 세션을 초기화한다
sess = tf.InteractiveSession()
sess.run(tf.global_variables_initializer())


# 1000번의 루프를 돌면서 학습을 진행한다
for _ in range(10000):
	batch_xs, batch_ys = next_batch(100)
	#print(batch_xs[0])
	#print(batch_ys[0])
	sess.run(train_step, feed_dict={x_input: batch_xs, y_input: batch_ys})
	costVal = sess.run(cross_entropy, feed_dict={x_input: batch_xs, y_input: batch_ys})
        # 일정주기로 cost 값을 확인한다 
	if _ % 3333 == 0:
	    print('step', _ , 'cost', costVal)
print("train done")



# 정답률을 계산한다
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_input, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
test_accuracy = sess.run(accuracy,feed_dict={x_input: test_images, y_input: test_labels})
print('test accuracy', test_accuracy)


#----------------------------------------------
# 임의의 얼굴 하나를 출력한 다음 맞혀보는 코드 
r = random.randint(0, _num_examples -1)
print ("Label: ", sess.run(tf.argmax(test_labels[r:r+1], 1)))
print ("Prediction: ", sess.run(tf.argmax(y_conv, 1), {x:test_images[r:r+1], keep_prob:1.0}))

plt.imshow(test_images[r:r+1].reshape(52, 52), cmap='gray', interpolation='nearest')
plt.show()



