#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술 part3_2, 신호등 색깔을 맞추는 모델을 만들고 학습시킨 후 
                                        이 ranking 코드를 사용해 기울기를 잰 다음 
                                        제일 기울기가 큰 사람이 좋은 점수를 받는다
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
base_image_path = "test_images/"
image_types = ["red", "green", "yellow"]
input_img_x = 32
input_img_y = 32
batch_size = 32
student_id = "20101447"

base_work_dir = "../deep_learning_traffic_light_%s" % (student_id)
checkpoint_name = "%s/model.ckpt" % (base_work_dir)

# Helper layer functions
def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def conv2d(x, W, stride):
    return tf.nn.conv2d(x, W, strides=[1, stride, stride, 1], padding='SAME')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')


x = tf.placeholder(tf.float32, shape=[None, input_img_x, input_img_y, 3])


# Model - THIS PART WILL BE REPLACED WITH THE CONTENTS IN model.txt.

contents = open('%s/model.txt' % (base_work_dir), 'r').read()
exec(contents)


# LOAD TEST SET

test_set = []

for im_type in image_types:
    for ex in glob.glob(os.path.join(base_image_path, im_type, "*")):
        im = cv2.imread(ex)
        if not im is None:
            im = cv2.resize(im, (32, 32))

            # Create an array representing our classes and set it
            one_hot_array = [0] * len(image_types)
            one_hot_array[image_types.index(im_type)] = 1

            assert(im.shape == (32, 32, 3))

            test_set.append((im, one_hot_array, ex))

test_x, test_y, test_z = zip(*test_set)


# TEST
zipped_x_y = list(zip(test_x, test_y))
conf_true = []
conf_pred = []
total_count = 0
correct_count = 0

start = time.time()

with tf.Session() as sess:
    saver.restore(sess, checkpoint_name)
#    optimistic_restore(sess, checkpoint_name)
    print("Model restored.")

    for tt in range(0, len(zipped_x_y)):
        q = zipped_x_y[tt]
        sfmax = list(sess.run(tf.nn.softmax(y.eval(feed_dict={x: [q[0]]})))[0])
        sf_ind = sfmax.index(max(sfmax))

        predicted_label = image_types[sf_ind]
        actual_label = image_types[q[1].index(max(q[1]))]

        if predicted_label == actual_label:
            correct_count = correct_count + 1

        total_count = total_count + 1
        if total_count % 100 == 0:
            print(total_count)

end = time.time()
accuracy = correct_count / total_count
timeTaken = end - start
print("Accuracy = %.6f, Time = %.6f sec" % (accuracy, timeTaken))
print("Slope = %.6f" % ((accuracy - 0.5) / timeTaken))



































