#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술 part3_3, Swedish traffic sign data에서 가져온 
                                        annotations.txt와 사진데이터를 사용해서 
                                        사진에서 Traffic Sign들을 추출한 다음 
                                        Deep Learning을 사용해 무슨 표지판인지 맞춰보는 코드

    여기서 사진데이터를 다운받을 수 있다
    http://www.cvl.isy.liu.se/research/datasets/traffic-signs-dataset/

    ONE HOT VECTOR  
       length : 19

        0  : 30_SIGN
        1  : 50_SIGN
        2  : 60_SIGN
        3  : 70_SIGN
        4  : 80_SIGN
        5  : 90_SIGN
        6  : 100_SIGN
        7  : 110_SIGN 
        8  : 120_SIGN
        9  : GIVE_WAY
        10 : NO_PARKING
        11 : PEDESTRIAN_CROSSING 
        12 : OTHER
        13 : PRIORITY_ROAD
        14 : PASS_RIGHT_SIDE
        15 : PASS_LEFT_SIDE
        16 : URDBL
        17 : NO_STOPPING_NO_STANDING 
        18 : PASS_EITHER_SIDE

'''
import sys,os,time
import math, random
import cv2
import os
import math
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

#--------------------------------------------------------------------------------------
# START OF DATA PREPROCESSING
#--------------------------------------------------------------------------------------
img_path = 'E:\\ml_dataset\\Set1Part0\\'
img_fnames = os.listdir(img_path)

annotations = open(img_path + 'annotations.txt')

img_name = []
traffic_signs = []
split_data = []
counter = 0

# annotations.txt에서 이미지와 표지판 데이터를 분리시킵니다
for line in annotations:
    split_data.append(line.split(':'))

    img_name.append(split_data[counter][0])
    traffic_signs.append(split_data[counter][1])

    counter += 1


# 표지판 데이터는 사각형좌표와 정보데이터를 분리합니다 (';', ',')로 두번 분리해야 합니다
for i in range(0, len(traffic_signs)):
    traffic_signs[i] = traffic_signs[i].split(';')
    
for i in range(0, len(traffic_signs)):
    for j in range(0, len(traffic_signs[i])):
        traffic_signs[i][j] = traffic_signs[i][j].split(',')
    

# 이미지와 4개의 좌표를 받아서 이미지를 자른 후 저장하는 함수
def img_trim(img, x1, y1, x2, y2, name1, name2, delimiter):
    # 최종적으로 Trim할 좌표를 str-->float-->int형으로 받아와야하므로 이와같이 처리합니다
    x1 = int(float(x1))
    x2 = int(float(x2))
    y1 = int(float(y1))
    y2 = int(float(y2))

    # width, height를 구합니다
    w = x1 - x2
    h = y1 - y2
    assert(w > 0)
    assert(h > 0)

    # name1에 .jpg를 전부 지웁니다
    name1 = name1.replace('.jpg','')

    img_trim = img[y2:y2+h, x2:x2+w]

    cv2.imwrite('./swConvTech_part3_3/cropped_img_forSW/' + str(name1) + delimiter + str(name2) + '.jpg', img_trim)





# 루프를 돌면서 표지판 데이터를 Trim 합니다
for i in range(0, len(traffic_signs)):
    img = cv2.imread(img_path + img_name[i])
    if(len(traffic_signs[i]) >= 2):
        # 만약 표지판데이터가 있다면 그 좌표를 읽어서 크기만큼 Trim 합니다
        for j in range(0, len(traffic_signs[i])):
            if(len(traffic_signs[i][j]) > 4):

                x1 = traffic_signs[i][j][1]
                y1 = traffic_signs[i][j][2]
                x2 = traffic_signs[i][j][3]
                y2 = traffic_signs[i][j][4]

                name = traffic_signs[i][j][6]
                print('i : %d' % i ,x1,y1,x2,y2)
                
                # 좌표와 이름을 파라미터에 넣고 함수를 호출합니다. 
                # 파일이름의 구분자는 '-'입니다
                img_trim(img,x1,y1,x2,y2, img_name[i], name, '-')
    else:
        continue

#--------------------------------------------------------------------------------------
# END OF DATA PREPROCESSING
#--------------------------------------------------------------------------------------
# IMAGE LOAD
#--------------------------------------------------------------------------------------
import sys,os,time
import math, random
import cv2
import os
import math
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

# 잘려진 이미지들의 파일이름을 전부 불러옵니다
cropped_img_path = 'E:\\gitrepo\\lockdpwn\\python_archive\\ipython\\swConvTech_part3_3\\cropped_img_forSW'
cropped_img_fnames = os.listdir(cropped_img_path)


traffic_images = []
traffic_label = []
split_cropped_img = []

# 사진이름이 [원본이름]-[정답].jpg로 되어있으므로 -로 이름을 우선 구분합니다
# traffic_image에 사진데이터를 불러옵니다
for line in cropped_img_fnames:
    traffic_images.append(cv2.imread(cropped_img_path + "\\"+ line))
    split_cropped_img.append(line.split('-'))


# traffic_label 데이터에 정답데이터를 넣습니다
for i in range(0, len(split_cropped_img)):
    split_cropped_img[i][1] = split_cropped_img[i][1].replace(' ','')
    split_cropped_img[i][1] = split_cropped_img[i][1].replace('.jpg','')
    traffic_label.append(split_cropped_img[i][1])


traffic_images = np.array(traffic_images)
traffic_label = np.array(traffic_label)


# 임의의 사진이 잘 나오는지 확인합니다
#r = random.randint(0, len(traffic_images)-1)
#print(r)
#print(traffic_label[r])
#plt.imshow(traffic_images[r], cmap='gray', interpolation='nearest')
#plt.show()

# Basic parameters
max_epochs = 25
base_image_path = "5_tensorflow_traffic_light_images/"
image_types = ["red", "green", "yellow"]
input_img_x = 32
input_img_y = 32
train_test_split_ratio = 0.9
batch_size = 32
checkpoint_name = "./part3_3.ckpt"


# Helper layer functions
def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def conv2d(x, W, stride):
    return tf.nn.conv2d(x, W, strides=[1, stride, stride, 1], padding='SAME')

# drop out# Function added for VALID option
def conv2d_valid(x, W, stride):
    return tf.nn.conv2d(x, W, strides=[1, stride, stride, 1], padding='VALID')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')

# Model
x = tf.placeholder(tf.float32, shape=[None, input_img_x, input_img_y, 3])
y_ = tf.placeholder(tf.float32, shape=[None, 19])

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

W_fc1 = weight_variable([n2*n3*n4, 3000])
b_fc1 = bias_variable([3000])

h_pool1_flat = tf.reshape(h_conv4, [-1, n2*n3*n4]) 
h_fc1 = tf.nn.relu(tf.matmul(h_pool1_flat, W_fc1) + b_fc1) # (3,3) ==> (3000,1)


# 2nd Fully Connected layer------------------------
W_fc2 = weight_variable([3000, 19])
b_fc2 = bias_variable([19])

y = tf.matmul(h_fc1, W_fc2) + b_fc2  # (3000,1) ==> (3,1)


saver = tf.train.Saver({'W_conv1' : W_conv1, 'b_conv1' : b_conv1, 'W_conv2' : W_conv2,'b_conv2' : b_conv2, 'W_conv3' : W_conv3, 'b_conv3' : b_conv3, 'W_conv4' : W_conv4,'b_conv4' : b_conv4, 'W_fc1' : W_fc1, 'b_fc1' : b_fc1, 'W_fc2' : W_fc2, 'b_fc2' : b_fc2})
#END-------------------------------------------------------------------------


sess = tf.InteractiveSession()

# Our loss function and optimizer
#  loss func, optimizer 변경하고 싶으면 변경하면 된다
loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels = y_, logits = y))
train_step = tf.train.AdamOptimizer(1e-4, 0.9).minimize(loss)

sess.run(tf.initialize_all_variables())

v_loss = least_loss = 99999999

# ONE HOT VECTOR index를 받아서 이름을 반환하는 함수
def recognizeOneHot(index):
'''
    ONE HOT VECTOR
       length : 19

        0  : 30_SIGN
        1  : 50_SIGN
        2  : 60_SIGN
        3  : 70_SIGN
        4  : 80_SIGN
        5  : 90_SIGN
        6  : 100_SIGN
        7  : 110_SIGN 
        8  : 120_SIGN
        9  : GIVE_WAY
        10 : NO_PARKING
        11 : PEDESTRIAN_CROSSING 
        12 : OTHER
        13 : PRIORITY_ROAD
        14 : PASS_RIGHT_SIDE
        15 : PASS_LEFT_SIDE
        16 : URDBL
        17 : NO_STOPPING_NO_STANDING 
        18 : PASS_EITHER_SIDE

'''
    if(index == 0):
        name = '30_SIGN [0]'
    elif(index == 1):
        name = '50_SIGN [1]'
    elif(index == 2):
        name = '60_SIGN [2]'
    elif(index == 3):
        name = '70_SIGN [3]'
    elif(index == 4):
        name = '80_SIGN [4]'
    elif(index == 5):
        name = '90_SIGN [5]'
    elif(index == 6):
        name = '100_SIGN [6]'
    elif(index == 7):
        name = '110_SIGN [7]'
    elif(index == 8):
        name = '120_SIGN [8]'
    elif(index == 9):
        name = 'GIVE_WAY [9]'
    elif(index == 10):
        name = 'NO_PARKING [10]'
    elif(index == 11):
        name = 'PEDESTRIAN_CROSSING [11]'
    elif(index == 12):
        name = 'OTHER [12]'
    elif(index == 13):
        name = 'PRIORITY_ROAD [13]'
    elif(index == 14):
        name = 'PASS_RIGH_SIDE [14]'
    elif(index == 15):
        name = 'PASS_LEFT_SIDE [15]'
    elif(index == 16):
        name = 'URDBL [16]'
    elif(index == 17):
        name = 'NO_STOPPING_NO_STANDING [17]'
    elif(index == 18):
        name = 'PASS_EITHER_SIDE [18]'

    return name



# Load data, [img, one_hot_array]
full_set = [] 

# 사진데이터를 32x32로 reshape하고 one hot vector를 만든다
for i in range(0, len(traffic_images)):
    traffic_images[i] = cv2.resize(traffic_images[i], (32,32))

    one_hot_array = [0] * 19
    # 각 index에 표지판 이름을 설정한다
    if(traffic_label[i] == '30_SIGN'):
        one_hot_array[0] = 1
    elif(traffic_label[i] == '50_SIGN'):
        one_hot_array[1] = 1
    elif(traffic_label[i] == '60_SIGN'):
        one_hot_array[2] = 1
    elif(traffic_label[i] == '70_SIGN'):
        one_hot_array[3] = 1
    elif(traffic_label[i] == '80_SIGN'):
        one_hot_array[4] = 1
    elif(traffic_label[i] == '90_SIGN'):
        one_hot_array[5] = 1
    elif(traffic_label[i] == '100_SIGN'):
        one_hot_array[6] = 1
    elif(traffic_label[i] == '110_SIGN'):
        one_hot_array[7] = 1
    elif(traffic_label[i] == '120_SIGN'):
        one_hot_array[8] = 1
    elif(traffic_label[i] == 'GIVE_WAY'):
        one_hot_array[9] = 1
    elif(traffic_label[i] == 'NO_PARKING'):
        one_hot_array[10] = 1
    elif(traffic_label[i] == 'PEDESTRIAN_CROSSING'):
        one_hot_array[11] = 1
    elif(traffic_label[i] == 'OTHER'):
        one_hot_array[12] = 1
    elif(traffic_label[i] == 'PRIORITY_ROAD'):
        one_hot_array[13] = 1
    elif(traffic_label[i] == 'PASS_RIGHT_SIDE'):
        one_hot_array[14] = 1
    elif(traffic_label[i] == 'PASS_LEFT_SIDE'):
        one_hot_array[15] = 1
    elif(traffic_label[i] == 'URDBL'):
        one_hot_array[16] = 1
    elif(traffic_label[i] == 'NO_STOPPING_NO_STANDING'):
        one_hot_array[17] = 1
    elif(traffic_label[i] == 'PASS_EITHER_SIDE'):
        one_hot_array[18] = 1

    full_set.append((traffic_images[i], one_hot_array))
    

#  모든 데이터를 받아서 랜덤으로 섞는다 
random.shuffle(full_set)

split_index = int(math.floor(len(full_set) * train_test_split_ratio))
train_set = full_set[:split_index]
test_set = full_set[split_index:]

# We ensure that our training and test sets are a multiple of batch size
train_set_offset = len(train_set) % batch_size
test_set_offset = len(test_set) % batch_size
train_set = train_set[: len(train_set) - train_set_offset]
test_set = test_set[: len(test_set) - test_set_offset]

train_x, train_y = zip(*train_set)
test_x, test_y   = zip(*test_set)


#------------------------------------------------------------------------
print("Starting training... [{} training examples]".format(len(train_x)))
v_loss = 9999999
train_loss = []
val_loss = []


for i in range(0, max_epochs):
    # Iterate over our training set
    for tt in range(0, (len(train_x) // batch_size)):
        start_batch = batch_size * tt
        end_batch = batch_size * (tt + 1)
        train_step.run(feed_dict={x: train_x[start_batch:end_batch], y_: train_y[start_batch:end_batch]})

    t_loss = loss.eval(feed_dict={x: train_x, y_: train_y})
    v_loss = loss.eval(feed_dict={x: test_x,  y_: test_y})
    
    train_loss.append(t_loss)
    val_loss.append(v_loss)

    sys.stdout.write("Epoch {:5}: loss: {:15.10f}, val. loss: {:15.10f}".format(i + 1, t_loss, v_loss))

    #  v_loss가 제일 낮을 경우에만 파라미터를 저장한다
    if v_loss < least_loss:
        sys.stdout.write(", saving new best model to {}".format(checkpoint_name))
        least_loss = v_loss
        filename = saver.save(sess, checkpoint_name)

    sys.stdout.write("\n")



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


#----------------------------------------------
# 임의의 표지판 하나를 출력한 다음 맞혀보는 코드 
r = random.randint(0, len(test_x)-1)
print(r)
traffic_name = []
traffic_name_pred = []
index = sess.run(tf.argmax(y, 1), feed_dict={x:test_x[r:r+1]})[0]

for i in range(0, 19):
    if(test_y[r][i] == 1):
        traffic_name = recognizeOneHot(i)

traffic_name_pred = recognizeOneHot(index)

print ("Label: ", traffic_name)
print ("Prediction: ", traffic_name_pred )

test_x = np.array(test_x)
plt.imshow(test_x[r].reshape(32, 32, 3), cmap='gray', interpolation='nearest')
plt.show()
#----------------------------------------------






