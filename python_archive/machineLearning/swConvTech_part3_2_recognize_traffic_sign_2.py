#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술 part3_2, 신호등 사진을 주면 색깔을 맞혀보는 프로젝트
                                               정확도 & 시간을 둘 다 고려해서 모델을 맞춰야 한다

                                               4 CNN & 3 Max pooling layer (3 SAME, 1 VALID)
                                               1 fully connected layer
                                               drop out
'''
%matplotlib inline

import sys, os, time
import itertools
import math, random
import glob
import tensorflow as tf
import numpy as np
import cv2
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
from IPython.display import Image, display
import warnings
warnings.filterwarnings('ignore')

# Basic parameters
max_epochs = 25
base_image_path = "5_tensorflow_traffic_light_images/"
image_types = ["red", "green", "yellow"]
input_img_x = 32
input_img_y = 32
train_test_split_ratio = 0.9
batch_size = 32
checkpoint_name = "./model.ckpt"


# Helper layer functions
def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def conv2d(x, W, stride):
    return tf.nn.conv2d(x, W, strides=[1, stride, stride, 1], padding='SAME')

# Function added for VALID option
def conv2d_valid(x, W, stride):
    return tf.nn.conv2d(x, W, strides=[1, stride, stride, 1], padding='VALID')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')


# Model
x = tf.placeholder(tf.float32, shape=[None, input_img_x, input_img_y, 3])
y_ = tf.placeholder(tf.float32, shape=[None, len(image_types)])


# Model - THIS PART SHOULD BE SAVED SEPARATELY IN "model.txt" file, SO IT CAN BE RETRIEVED AUTOMATICALLY BY "ranking.ipynb"
#  꼭 model.txt 파일을 사용해야하고 이름을 바꾸면 안된다!
#START-------------------------------------------------------------------------
# 4 CNN & 3 Max pooling layer (3 SAME, 1 VALID)
# 1 fully connected layer
# drop out
x_image = x

# 1st conv layer-----------------------------
W_conv1 = weight_variable([3, 3, 3, 16])
b_conv1 = bias_variable([16])

h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1, 1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1) # (32,32) ==> (16,16)


# 2nd conv layer-----------------------------
W_conv2 = weight_variable([5,5,16,32])
b_conv2 = weight_variable([32]) 

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2, 1) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2) # (16,16) ==> (8,8)


# 3rd conv layer-----------------------------
W_conv3 = weight_variable([3,3,32,64])
b_conv3 = weight_variable([64])

h_conv3 = tf.nn.relu(conv2d_valid(h_pool2, W_conv3, 1) + b_conv3) # (8,8) ==> (6,6)
h_pool3 = max_pool_2x2(h_conv3) # (6,6) ==> (3,3)


# 4th conv layer-----------------------------
W_conv4 = weight_variable([4,4,64,128])
b_conv4 = weight_variable([128])

h_conv4 = tf.nn.relu(conv2d(h_pool3, W_conv4, 1) + b_conv4) # (3,3) ==> (3,3)


# 1st Fully Connected layer------------------------
n1, n2, n3, n4 = h_conv4.get_shape().as_list()

W_fc1 = weight_variable([n2*n3*n4, 3])
b_fc1 = bias_variable([3])

h_pool1_flat = tf.reshape(h_conv4, [-1, n2*n3*n4]) 


# Dropout-----------------------------------------
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_pool1_flat, keep_prob)

y= tf.matmul(h_fc1_drop, W_fc1) + b_fc1 # (3,3) ==> (3,1)


saver = tf.train.Saver({'W_conv1' : W_conv1, 'b_conv1' : b_conv1, 'W_conv2' : W_conv2,'b_conv2' : b_conv2, 'W_conv3' : W_conv3, 'b_conv3' : b_conv3, 'W_conv4' : W_conv4,'b_conv4' : b_conv4, 'W_fc1' : W_fc1, 'b_fc1' : b_fc1})
#END-------------------------------------------------------------------------


sess = tf.InteractiveSession()


# Our loss function and optimizer
#  loss func, optimizer 변경하고 싶으면 변경하면 된다
loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels = y_, logits = y))
train_step = tf.train.AdamOptimizer(1e-4, 0.9).minimize(loss)
sess.run(tf.initialize_all_variables())

v_loss = least_loss = 99999999

# Load data
full_set = []

# base_image_path에서 모든 이미지 데이터를 읽어온다
for im_type in image_types:
    for ex in glob.glob(os.path.join(base_image_path, im_type, "*")):
        im = cv2.imread(ex)
        if not im is None:
            # 모든 이미지를 32x32로 리사이징한다
            im = cv2.resize(im, (32, 32))

            # one hot vector를 만든다 
            # Create an array representing our classes and set it
            one_hot_array = [0] * len(image_types)
            one_hot_array[image_types.index(im_type)] = 1

            assert(im.shape == (32, 32, 3))

            full_set.append((im, one_hot_array, ex))

#  모든 데이터를 받아서 랜덤으로 섞는다 
random.shuffle(full_set)

#  Train set, Test set을 나누는 코드 (9:1)
# We split our data into a training and test set here
split_index = int(math.floor(len(full_set) * train_test_split_ratio))
train_set = full_set[:split_index]
test_set = full_set[split_index:]

# We ensure that our training and test sets are a multiple of batch size
train_set_offset = len(train_set) % batch_size
test_set_offset = len(test_set) % batch_size
train_set = train_set[: len(train_set) - train_set_offset]
test_set = test_set[: len(test_set) - test_set_offset]

train_x, train_y, train_z = zip(*train_set)
test_x, test_y, test_z = zip(*test_set)

print("Starting training... [{} training examples]".format(len(train_x)))
v_loss = 9999999
train_loss = []
val_loss = []


for i in range(0, max_epochs):
    # Iterate over our training set
    for tt in range(0, (len(train_x) // batch_size)):
        start_batch = batch_size * tt
        end_batch = batch_size * (tt + 1)
        # keep_prob : 0.5로 훈련데이터를 학습한다
        train_step.run(feed_dict={x: train_x[start_batch:end_batch], y_: train_y[start_batch:end_batch], keep_prob:0.5})
        ex_seen = "Current epoch, examples seen: {:20} / {} \r\n".format(tt * batch_size, len(train_x))
        sys.stdout.write(ex_seen.format(tt * batch_size))
        sys.stdout.flush()

    ex_seen = "Current epoch, examples seen: {:20} / {} \r\n".format((tt + 1) * batch_size, len(train_x))
    sys.stdout.write(ex_seen.format(tt * batch_size))
    sys.stdout.flush()

    t_loss = loss.eval(feed_dict={x: train_x, y_: train_y, keep_prob:1.0})
    v_loss = loss.eval(feed_dict={x: test_x, y_: test_y, keep_prob:1.0})
    
    train_loss.append(t_loss)
    val_loss.append(v_loss)

    sys.stdout.write("Epoch {:5}: loss: {:15.10f}, val. loss: {:15.10f}".format(i + 1, t_loss, v_loss))

    #  v_loss가 제일 낮을 경우에만 파라미터를 저장한다
    if v_loss < least_loss:
        sys.stdout.write(", saving new best model to {}".format(checkpoint_name))
        least_loss = v_loss
        filename = saver.save(sess, checkpoint_name)

    sys.stdout.write("\n")


# Training Finished
#----------------------------------------------------------------
# Analyze Start
#----------------------------------------------------------------
# Epoch-Loss 그래프를 그려주는 코드 
plt.figure()
plt.xticks(np.arange(0, len(train_loss), 1.0))
plt.ylabel("Loss")
plt.xlabel("Epochs")
train_line = plt.plot(range(0, len(train_loss)), train_loss, 'r', label="Train loss")
val_line = plt.plot(range(0, len(val_loss)), val_loss, 'g', label="Validation loss")
plt.legend()
plt.show()


# 훈련모델에 Test 데이터를 넣어본 다음 예측이 틀린 경우에만 출력하는 코드
zipped_x_y = list(zip(test_x, test_y))
conf_true = []
conf_pred = []

for tt in range(0, len(zipped_x_y)):
    q = zipped_x_y[tt]
    sfmax = list(sess.run(tf.nn.softmax(y.eval(feed_dict={x: [q[0]], keep_prob:1.0})))[0])
    sf_ind = sfmax.index(max(sfmax))
    
    predicted_label = image_types[sf_ind]
    actual_label = image_types[q[1].index(max(q[1]))]
    
    conf_true.append(actual_label)
    conf_pred.append(predicted_label)
    
    if predicted_label != actual_label:
        print("Actual: {}, predicted: {}".format(actual_label, predicted_label))
        img_path = test_z[tt]    
        ex_img = Image(filename=img_path)
        display(ex_img)



# confusion_matrix를 plot하는 함수
def plot_confusion_matrix(cm, classes,
                          normalize=False,
                          title='Confusion matrix',
                          cmap=plt.cm.Blues):
    """
    This function prints and plots the confusion matrix.
    Normalization can be applied by setting `normalize=True`.
    """
    plt.imshow(cm, interpolation='nearest', cmap=cmap)
    plt.title(title)
    plt.colorbar()
    tick_marks = np.arange(len(classes))
    plt.xticks(tick_marks, classes, rotation=45)
    plt.yticks(tick_marks, classes)

    cm2 = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]

    cm2 = np.around(cm2, 2)

    thresh = cm.max() / 2.
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, str(cm[i, j]) + " / " + str(cm2[i, j]),
                 horizontalalignment="center",
                 color="white" if cm[i, j] > thresh else "black")

    plt.tight_layout()
    plt.ylabel('True label')
    plt.xlabel('Predicted label')



# confusion_matrix를 출력하는 코드
cnf_matrix = confusion_matrix(conf_true, conf_pred)
plt.figure()
plot_confusion_matrix(cnf_matrix, classes=image_types, normalize=False,
                      title='Normalized confusion matrix')
plt.show()


