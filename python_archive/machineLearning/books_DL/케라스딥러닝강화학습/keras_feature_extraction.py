#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 케라스딥러닝강화학습 p138, VGG16 신경망에서 가중치를 불러온 다음
                                        고양이 사진을 예측해서 block4_pool 중간층의 feature_map을 추출해본 코드

                                        특정층의 feature map을 불러올 수 있다는게 흥미롭지만 어떻게 시각화를 하는지 모르겠다 :-0
'''

from keras.applications.vgg16 import VGG16
from keras.models import Model
from keras.preprocessing import image
from keras.applications.vgg16 import preprocess_input
import numpy as np


# ed:
base_model = VGG16(weights='imagenet', include_top=True)


for i, layer  in enumerate(base_model.layers ):
    print(i, layer.name, layer.output_shape)

    model = Model(inputs=base_model.input, outputs= base_model.get_layer('block4_pool').output)
    img_path = '/home/dyros-vehicle/Pictures/cat.jpg'

    img = image.load_img(img_path, target_size=(224,224))
    x = image.img_to_array(img)
    x = np.expand_dims(x, axis=0)
    x = preprocess_input(x)

    features = model.predict(x)
