#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==>
'''
from __future__ import print_function
from keras.layers.recurrent import SimpleRNN
from keras.models import Sequential
from keras.layers import Dense, Activation
import numpy as np
import keras.backend.tensorflow_backend as K


INPUT_FILE = "./data/alice_in_wonderland.txt"

print("Extracting text from input...")
fin = open(INPUT_FILE, 'rb')
lines = []

for line in fin:
    line = line.strip().lower()
    line = line.decode("ascii", "ignore")
    if len(line) == 0:
        continue

    lines.append(line)

fin.close()
text = " ".join(lines)

# creating lookup tables
# Here chars is the number of features in our character "vocabulary"

chars = set([c for c in text])
nb_chars = len(chars)
char2index = dict((c,i) for i, c in enumerate(chars))
index2char = dict((i,c) for i, c in enumerate(chars))


# create inputs and labels from the text. We do this by stepping
# through the text ${step} character at a time, and extracting a 
# sequence of size ${seqlen} and the next output char. For example,
# assuming an input text "The sky was falling", we would get the 
# following sequence of input_chars and label_chars (first 5 only)
#   The sky wa -> s
#   he sky was ->  
#   e sky was  -> f
#    sky was f -> a
#   sky was fa -> l
print("Creating input and label text...")
SEQLEN = 10
STEP = 1


input_chars = []
label_chars = []
for i in range(0, len(text) - SEQLEN, STEP):
    input_chars.append(text[i:i + SEQLEN])
    label_chars.append(text[i + SEQLEN])



# vectorize the input and label chars
# Each row of the input is represented by seqlen characters, each 
# represented as a 1-hot encoding of size len(char). There are 
# len(input_chars) such rows, so shape(X) is (len(input_chars),
# seqlen, nb_chars).
# Each row of output is a single character, also represented as a
# dense encoding of size len(char). Hence shape(y) is (len(input_chars),
# nb_chars).
print("Vectorizing input and label text...")
X = np.zeros((len(input_chars), SEQLEN, nb_chars), dtype=np.bool)
y = np.zeros((len(input_chars), nb_chars), dtype=np.bool)

for i,input_char in enumerate(input_chars):
    for j, ch in enumerate(input_char):
        X[i, j, char2index[ch]] = 1

    y[i, char2index[label_chars[i]]] = 1



HIDDEN_SIZE = 128
BATCH_SIZE = 128
NUM_ITERATIONS = 25
NUM_EPOCH_PER_ITERATION = 1
NUM_PREDS_PER_EPOCH = 100



with K.tf.device('/gpu:0'):
    model = Sequential()
    model.add(SimpleRNN(HIDDEN_SIZE, return_sequences=False,
            input_shape=(SEQLEN, nb_chars),
            unroll=True))
    model.add(Dense(nb_chars))
    model.add(Activation("softmax"))
    model.compile(loss="categorical_crossentropy", optimizer="rmsprop")




for iteration in  range(NUM_ITERATIONS):
    print("=" * 50)
    print("Iteration #: %d" % (iteration))

    model.fit(X, y, batch_size=BATCH_SIZE, epochs=NUM_EPOCH_PER_ITERATION)

    test_idx = np.random.randint(len(input_chars))
    test_chars = input_chars[test_idx]

    print("Generating from seed: %s" % (test_chars))
    print(test_chars, end="")

    for i in  range(NUM_PREDS_PER_EPOCH):
        Xtest = np.zeros((1, SEQLEN, nb_chars))

        for i, ch in  enumerate(test_chars):
            Xtest[0, i, char2index[ch]] = 1
        pred = model.predict(Xtest, verbose=0)[0]
        ypred = index2char[np.argmax(pred)]

        print(ypred, end="")
        test_chars = test_chars[1:] + ypred

    print()
        
    
