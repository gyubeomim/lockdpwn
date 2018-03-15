#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
	python ==>
'''
print("굳")
# from keras.layers import Merge
# from keras.layers.core import Dense, Reshape
# from keras.layers.embeddings import Embedding
# from keras.models import Sequential
# from keras.preprocessing.text import *
# from keras.preprocessing.sequence import skipgrams

# vocab_size = 5000
# embed_size = 300

# word_model = Sequential()
# word_model.add(Embedding(vocab_size, embed_size,
#                          embeddings_initializer="glorot_uniform",
#                          input_length=1))

# word_model.add(Reshape((embed_size,)))


# context_model = Sequential()
# context_model.add(Embedding(vocab_size, embed_size,
#                             embeddings_initializer="glorot_uniform",
#                             input_length=1))

# context_model.add(Reshape((embed_size,)))


# model = Sequential()

# model.add(Merge([word_model, context_model], mode="dot", dot_axes=0))
# model.add(Dense(1, kernel_initializer="glorot_uniform",
#                 activation="sigmoid"))

# model.compile(loss="mean_squared_error", optimizer="adam")
