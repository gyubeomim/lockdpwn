#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술, part2 프로젝트, 얼굴 사진 55x40 데이터를 700장 사용해 hyperparameter를 조정해가며 최고의 정답률이 나오는 hyperparameter를 찾아보는 프로젝트

                hyperparameter는 CNN의 필터크기, feature map 개수
                                 max pooling 필터크기
                                 train iteration 횟수
                                 learning_rate
                                 hidden layer 층수
                                 CNN 적용횟수
                                 fully connected layer 적용횟수
                                 batch size 크기

                                 등이 있다 

                                 1층짜리 모델

'''
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
import scipy.misc
import scipy.io
import random

#-----------------------------------------------------------------
# train
train_images = []
tlabels = []

# train Image 데이터 700장을 불러온다
for num in range(1,701):
    train_images.append(scipy.misc.imread('.\\swConvTech_part2\\train_image\\train_'+ str(num)+'.bmp'))

# train Label 데이터를 불러온다
with open(".\\swConvTech_part2\\train_label.txt") as f:
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
    test_images.append(scipy.misc.imread('.\\swConvTech_part2\\test_image\\test_'+ str(num)+'.bmp'))


# test Label 데이터를 불러온다
with open(".\\swConvTech_part2\\test_label.txt") as f:
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
test_images =  test_images / 255.


#-----------------------------------------------------------------

_num_examples = 700   # 데이터 갯수
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
x_input = tf.placeholder(tf.float32, [None, 2200])
y_input = tf.placeholder(tf.float32, [None, 100])

# 신경망 파라미터들 y = x*w + b
W = tf.Variable(tf.zeros([2200, 100]))
b = tf.Variable(tf.zeros([100]))
y = tf.matmul(x_input, W) + b


# softmax 알고리즘을 실행해서 y값을 최적화하고 cross_entropy를 정의한다
# softmax : 값을 0 ~ 1사이로 정규화시키는 함수 (총합은 1이 되도록 정규화하므로 확률로 변경하는 것과 같다)
# y = tf.nn.softmax(y)

learning_rate = 0.5 

# cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_input * tf.log(y), reduction_indices=[1]))
cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_input, logits=y))
# Gradient Descent 알고리즘을 사용해서 cross_entropy를 최소화한다. 학습율은 0.5
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)


init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)


# 정답률을 계산한다  y_input  vs  y
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_input, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))


#----------------------------------------------
batch_size = 50       # 한 루프에 몇개의 (Image, Label) 데이터를 학습하는지 설정
display_step = 100    # 루프를 돌면서 화면에 표시할 빈도 설정
iteration = 1000

# Training iterations
train_accuracies = []
test_accuracies = []

for i in range(iteration):
	costVal = 0.
	batch = next_batch(batch_size)
	

	train_accuracy = sess.run(accuracy,feed_dict={x_input:batch[0], y_input:batch[1]})
	test_accuracy = sess.run(accuracy,feed_dict={x_input: test_images, y_input: test_labels})
                
        # data added to plot
	train_accuracies.append(train_accuracy)
	test_accuracies.append(test_accuracy)
	# 실제 학습과정 함수, dropout 50%를 토대로 학습한다
	sess.run(optimizer,feed_dict={x_input:batch[0],y_input:batch[1]})

        # n번 돌릴 때마다 결과를 확인한다
	if i % display_step == 0:
		costVal = sess.run(cost, feed_dict={x_input: batch[0], y_input: batch[1]})

		print('step', i , 'training_accuracy', train_accuracy,'test_accuracy', test_accuracy,'cost', costVal)
		lastCostVal = costVal



print('[+] no hidden layer')
print('[+] learning_rate     : [', learning_rate, ']')
print('[+] iteration         : [', iteration, ']')
print('[+] batch_size        : [', batch_size, ']')
print('[+] cost              : [', lastCostVal, ']')
print('[+] training_accuracy : [', train_accuracy,']')
print('[+] test accuracy     : [', test_accuracy, ']')

plt.plot(train_accuracies, 'k-', label='Train Accuracy')
plt.plot(test_accuracies, 'r--', label='Test Accuracy')
plt.title('Match Ratio per Generation')
plt.xlabel('Generation')
plt.ylabel('Accuracy')
plt.legend(loc='upper right')
plt.show()


#----------------------------------------------
# 임의의 얼굴 하나를 출력한 다음 맞혀보는 코드 
r = random.randint(0, _num_examples -1)
print ("Label: ", sess.run(tf.argmax(test_labels[r:r+1], 1)))
print ("Prediction: ", sess.run(tf.argmax(y, 1), {x_input:test_images[r:r+1]}))

plt.imshow(test_images[r:r+1].reshape(55, 40), cmap='gray', interpolation='nearest')
plt.show()



