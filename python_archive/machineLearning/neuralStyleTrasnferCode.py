#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 비주얼컴퓨팅, 고흐의 그림의 화풍을 토대로 특정 사진을 변경하는 style transfer를 하는 코드
                           500mb 상당의 imagenet-vgg-verydeep-19 파일이 필요하다
'''
%matplotlib inline
# style = scipy.misc.imresize(style, target_shape[1] / style.shape[1])
# 여기서 int형 끼리 나눠지는 문제를 해결하기 위해 추가한다
from __future__ import division
import vgg
import matplotlib.pyplot as plt
import tensorflow as tf
import numpy as np
import scipy.io
import scipy.misc
import math
from PIL import Image


#-------------------------------------------------------------
def imread(path):
    img = scipy.misc.imread(path).astype(np.float)  # 사진을 처리 하기 전에 float형으로 바꿔준다. (astype(np.float)에서 색반전이 일어난다)
    if len(img.shape) == 2:
        # grayscale
        img = np.dstack((img,img,img))
    elif img.shape[2] == 4:
        # PNG with alpha channel
        img = img[:,:,:3]
    return img


# 사용하지 않는 함수
def imsave(path, img):
    img = np.clip(img, 0, 255).astype(np.uint8)  # 이미지를 rgb 0~255 값으로 clipping 해준다
    Image.fromarray(img).save(path, quality=95)


def _tensor_size(tensor):
    from operator import mul
    return reduce(mul, (d.value for d in tensor.get_shape()), 1)



#-------------------------------------------------------------
# style.jpg :   640 x 507
# content.jpg : 600 x 309
# 위 두장이 색이 반전되서 들어간다. 
# style.shape = (507, 640, 3)
# content.shape = (399, 600, 3)
style   = imread('style.jpg')
content = imread('content.jpg')


# 이미지 타입을 바꿔준다음 출력한다(다시 색상이 원래대로 돌아온다)
style_img   = style.astype(np.uint8)
content_img = content.astype(np.uint8)


# 이미지 출력
plt.subplot(1, 2, 1)
plt.imshow(style_img)
plt.axis('off')
plt.subplot(1, 2, 2)
plt.imshow(content_img)
plt.axis('off')



#-------------------------------------------------------------
# target_shape = (399, 600, 3)
target_shape = content.shape

# style = (507, 640, 3) --> (475, 600, 3) 으로 변경된다
style = scipy.misc.imresize(style, target_shape[1] / style.shape[1])

initial_noiseblend = 1.0
initial = content

CONTENT_WEIGHT = 5e0
STYLE_WEIGHT = 5e2
TV_WEIGHT = 1e2

STYLE_LAYER_WEIGHT_EXP = 1

LEARNING_RATE = 1e1
BETA1 = 0.9
BETA2 = 0.999
EPSILON = 1e-08

ITERATIONS = 100

POOLING = 'max'

from functools import reduce

# 콘텐츠 레이어 : 
# 스타일 레이어 :
# 원하는 relu들을 비교하기 위해 선언한다
# 내가 원하는 relu 들로 설정할 수 있다
CONTENT_LAYERS = ('relu4_2', 'relu5_2')
STYLE_LAYERS = ('relu1_1', 'relu2_1', 'relu3_1', 'relu4_1', 'relu5_1')


# shape = (1, 399, 600, 3)
# style_shape = (1, 475, 600, 3)
shape = (1,) + content.shape
style_shape = (1,) + style.shape



#-------------------------------------------------------------
# 500mb 상당의 파일을 로딩한다
# classes, layer, normalization 
# vgg_mean_pixel = ([123.68, 116.779, 103.939])
vgg_weights, vgg_mean_pixel = vgg.load_net('imagenet-vgg-verydeep-19.mat')


layer_weight = 1.0
style_layers_weights = {}

# relu1_1 ~ relu5_1 까지 전부 1.0
for style_layer in STYLE_LAYERS:
    style_layers_weights[style_layer] = layer_weight
    layer_weight *= STYLE_LAYER_WEIGHT_EXP    
 

# normalize style layer weights
# relu1_1 ~ relu5_1 까지 전부 0.2가 된다
layer_weights_sum = 0
for style_layer in STYLE_LAYERS:
    layer_weights_sum += style_layers_weights[style_layer]
for style_layer in STYLE_LAYERS:
    style_layers_weights[style_layer] /= layer_weights_sum



#-------------------------------------------------------------
# 
# compute content features in feedforward mode
content_features = {}

g = tf.Graph()
with g.as_default(), g.device('/cpu:0'), tf.Session() as sess:
    # image = <tf.Tensor 'Placeholder:0' shape=(1, 399, 600, 3) dtype=float32>
    image = tf.placeholder('float', shape=shape)  
    net = vgg.net_preloaded(vgg_weights, image, POOLING)  # 기존의 vgg net을 갖다쓴다
    # content_pre = (1, 399, 600, 3)
    content_pre = np.array([vgg.preprocess(content, vgg_mean_pixel)])  # 입력으로 줄 이미지를 준비한다
    
    for layer in CONTENT_LAYERS:
        #content_features.keys() ==> ['relu4_2','relu5_2']
        # content 사진을 넣었을 때 net의 값을 저장해놓는다
        content_features[layer] = net[layer].eval(feed_dict={image: content_pre})  # network를 evaluation해서 각 콘텐츠의 feature를 뽑아낸다






#-------------------------------------------------------------
# compute style features in feedforward mode
style_features = {}

# vggnet의 입력은 보통 224 x 224  for training
# 하지만 test는 아무개 x 아무개의 이미지가 들어올 수 있다
# 그런데 고흐의 그림은 픽셀이 정해져 있으므로 test 이미지와 다를 수 있다
# 따라서 고흐의 그림과 test 이미지를 비교할 수 있는 같은 차원의 activation map 행렬이 필요하다
# 따라서 자기끼리 (n,(r,c,)) x ((r,c,),n)  = n x n 행렬을 만드는 연산을 하는 것이다
g = tf.Graph()
with g.as_default(), g.device('/cpu:0'), tf.Session() as sess:
    # image = (1, 475, 600, 3)
    image = tf.placeholder('float', shape=style_shape)
    net = vgg.net_preloaded(vgg_weights, image, POOLING)
    # style_pre = (1, 475 ,600, 3)
    style_pre = np.array([vgg.preprocess(style, vgg_mean_pixel)])
    
    for layer in STYLE_LAYERS:
        # features = (1140, 512) 마지막 루프값인듯
        features = net[layer].eval(feed_dict={image: style_pre})
        features = np.reshape(features, (-1, features.shape[3]))
        
        # style feature를 n x n화 시킨다
        # gram = (512, 512)
        gram = np.matmul(features.T, features) / features.size
        # style_features.keys() = ('relu2_1', 'relu5_1', 'relu4_1', 'relu1_1', 'relu3_1')
        style_features[layer] = gram




#-------------------------------------------------------------

initial_content_noise_coeff = 1.0 - initial_noiseblend
# initial == content.jpg
# initial = (399, 600, 3) --> (1, 399 ,600, 3)
initial = np.array([vgg.preprocess(initial, vgg_mean_pixel)])
# float32 형으로 변환시킨다
initial = initial.astype(np.float32)
# noise = (1, 399, 600 ,3)
noise = np.random.normal(size=shape, scale=np.std(content) * 0.1)

initial = (initial) * initial_content_noise_coeff + (tf.random_normal(shape) * 0.256) * (1.0 - initial_content_noise_coeff)

image = tf.Variable(initial)
# net.keys() = ('conv3_2', 'conv4_4', 'conv1_2', 'conv3_4', 'conv2_2', 'conv2_1', 'conv4_3', 'relu4_2', 'pool2', 'relu5_4', 'relu5_1', 'relu4_1', 'conv5_3', 'pool1', 'conv3_1', 'conv5_1', 'relu1_1', 'conv5_2', 'relu1_2', 'relu3_3', 'pool3', 'pool4', 'conv5_4', 'relu5_2', 'relu4_3', 'relu2_1', 'conv3_3', 'relu3_2', 'conv1_1', 'relu3_4', 'conv4_2', 'relu4_4', 'relu5_3', 'relu2_2', 'conv4_1', 'relu3_1')
net = vgg.net_preloaded(vgg_weights, image, POOLING)






#-------------------------------------------------------------
# content loss     
# 타겟사진의 특정 컨벌루션 지점에서 추출한 결과(activation map)와 
# 합성물에서 중간에 추출한 결과가 얼마나 비슷한지를 loss fuction으로 하는듯
content_layers_weights = {}
content_layers_weights['relu4_2'] = 1.0   # 가중치를 얼마줄건지 우리가 직접 설정할 수 있다
content_layers_weights['relu5_2'] = 1.0 - content_layers_weights['relu4_2']


content_loss = 0
content_losses = []

for content_layer in CONTENT_LAYERS:
    content_losses.append(content_layers_weights[content_layer] * CONTENT_WEIGHT * (2 * tf.nn.l2_loss(
            net[content_layer] - content_features[content_layer]) /
            content_features[content_layer].size))

content_loss += reduce(tf.add, content_losses)



#-------------------------------------------------------------
# style loss
style_loss = 0
style_losses = []

for style_layer in STYLE_LAYERS:
    # gram Matrix를 만든다
    layer = net[style_layer]
    _, height, width, number = map(lambda i: i.value, layer.get_shape())
    size = height * width * number
    feats = tf.reshape(layer, (-1, number))
    gram = tf.matmul(tf.transpose(feats), feats) / size
    style_gram = style_features[style_layer]

    style_losses.append(style_layers_weights[style_layer] * 2 * tf.nn.l2_loss(gram - style_gram) / style_gram.size)

style_loss += STYLE_WEIGHT * reduce(tf.add, style_losses)



#-------------------------------------------------------------
# total variation denoising
# image = tf.Variable (1, 399, 600, 3) float32
# tv_y_size = 716400
# tv_x_size = 717003
tv_y_size = _tensor_size(image[:,1:,:,:])
tv_x_size = _tensor_size(image[:,:,1:,:])

# tv loss : 사진에서 윗부분과 아랫부분을 뺀 값을 최소화하는 방향으로 최소화한다
tv_loss = TV_WEIGHT * 2 * (
        # 윗부분
        (tf.nn.l2_loss(image[:,1:,:,:] - image[:,:shape[1]-1,:,:]) / tv_y_size) +  
        # 아랫부분
        (tf.nn.l2_loss(image[:,:,1:,:] - image[:,:,:shape[2]-1,:]) / tv_x_size))


# overall loss
loss = content_loss + style_loss + tv_loss

# optimizer setup
train_step = tf.train.AdamOptimizer(LEARNING_RATE, BETA1, BETA2, EPSILON).minimize(loss)




#-------------------------------------------------------------
# optimization
best_loss = float('inf')
best = None

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    print('Optimization started...')            

    for i in range(ITERATIONS):
        if i % 100 == 0:
            print('Iteration %4d/%4d' % (i + 1, ITERATIONS))
        train_step.run()
        last_step = (i == ITERATIONS - 1)

        if last_step:
            print('  content loss: %g' % content_loss.eval())
            print('    style loss: %g' % style_loss.eval())
            print('       tv loss: %g' % tv_loss.eval())
            print('    total loss: %g' % loss.eval())

            this_loss = loss.eval()
            if this_loss < best_loss:
                best_loss = this_loss
                best = image.eval()

            img_out = vgg.unprocess(best.reshape(shape[1:]), vgg_mean_pixel)




#-------------------------------------------------------------
# img_out은 float형이고 (-)(+)값이 제각각이므로 아래와 같이 데이터를 정제 후 출력해야 한다  
img = np.clip(img_out, 0, 255).astype(np.uint8)
plt.imshow(img)
