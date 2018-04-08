#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
	python ==> 케라스딥러닝강화학습 p195, word2vec 모델 중 하나인 skipgrams를 이용해 중심단어가 주어졌을 때 주변단어를 예측하는 코드
'''

from keras.layers import Merge
from keras.layers.core import Dense, Reshape
from keras.layers.embeddings import Embedding
from keras.models import Sequential
from keras.preprocessing.text import *
from keras.preprocessing.sequence import skipgrams

vocab_size = 5000
embed_size = 300
text = "I love green eggs and ham"
# text = "trainval.txt contains indices to all the images in the training data. In our experiments, we randomly split half of indices in trainval.txt into train.txt to form a training set and rest of them into val.txt to form a validation set. For your convenience, we provide a script to split the train-val set automatically. Simply run"


word_model = Sequential()
word_model.add(Embedding(vocab_size, embed_size,
                         embeddings_initializer="glorot_uniform",
                         input_length=1))

word_model.add(Reshape((embed_size,)))


context_model = Sequential()
context_model.add(Embedding(vocab_size, embed_size,
                            embeddings_initializer="glorot_uniform",
                            input_length=1))

context_model.add(Reshape((embed_size,)))


# ed: 위 두 word_model과 context_model을 합쳐서 model의 입력이 된다
model = Sequential()

model.add(Merge([word_model, context_model], mode="dot", dot_axes=0))
model.add(Dense(1, kernel_initializer="glorot_uniform",
                activation="sigmoid"))

model.compile(loss="mean_squared_error", optimizer="adam")



tokenizer = Tokenizer()
tokenizer.fit_on_texts([text])

word2id = tokenizer.word_index
id2word = {v:k for k,v in word2id.items()}

wids = [word2id[w] for w in text_to_word_sequence(text)]
pairs, labels = skipgrams(wids, len(word2id))

print(len(pairs), len(labels))
print("\n")
for i  in range(10):
	print("[ {:s} ({:d}), {:s} ({:d}) ] -> {:d}".format(
		id2word[pairs[i][0]], pairs[i][0],
		id2word[pairs[i][1]], pairs[i][1],
		labels[i]))
