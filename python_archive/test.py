#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
	python ==> 케라스딥러닝강화학습 p
'''

from keras.models import Sequential
from keras.layers.core import Dense, Lambda
from keras.layers.embeddings import Embedding
import keras.backend as K


vocab_size = 5000
embed_size = 300
window_size = 1
text = "I love green eggs and ham"


model = Sequential()
model.add(Embedding(input_dim=vocab_size, output_dim=embed_size,
					embeddings_initializer='glorot_uniform',
					input_length=window_size*2))


model.add(Lambda(lambda x: K.mean(x, axis=1), output_shape=(embed_size,)))
model.add(Dense(vocab_size, kernel_initializer='glorot_uniform',
				activation='softmax'))

model.compile(loss='categorical_crossentropy', optimizer='adam')

