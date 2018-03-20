#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
	python ==> 케라스딥러닝강화학습 p
'''

from gensim.models import word2vec
import logging
import os


class Text8Sentences(object):
	def __init__(self, fname, maxlen):
		self.fname = fname
		self.maxlen = maxlen


	def __iter__(self):
		with open(os.path.join(DATA_DIR, "text8"), "rb") as ftext:
			text = ftext.read().split(" ")
			words =[]

<<<<<<< HEAD

model.add(Lambda(lambda x: K.mean(x, axis=1), output_shape=(embed_size,)))
model.add(Dense(vocab_size, kernel_initializer='glorot_uniform',
				activation='softmax'))

model.compile(loss='categorical_crossentropy', optimizer='adam')
=======
			for word  in text :
				if len(words) >= self.maxlen:
					yield words
					words = []
				words.append(word)
			yield words
>>>>>>> 5b577484c1a14ce8b1d8ad22314a9a2144f3703b



logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)
# DATA_DIR = "../data"
DATA_DIR = "/media/dyros-vehicle/edward_6/"
sentences = Text8Sentences(os.path.join(DATA_DIR, "text8"), 50)
model = word2vec.Word2Vec(sentences, size=300, min_count=30)

model.most_similar("woman")
model.most_similar(positive=['woman', 'king'], negative=['man'])

# ed: model 결과벡터를 정규화하고 저장한다
model.init_sims(replace=True)
model.save("word2vec_gensim.bin")
