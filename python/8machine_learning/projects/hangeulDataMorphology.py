#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 비주얼컴퓨팅, 한글파일 kalph_train을 랜덤으로 모폴로지연산을 한 다음 modified_file로 저장하는 코드 
'''
import h5py
import cv2
import random
import numpy as np
import matplotlib.pyplot as plt

def getDataFromFile(path):
    # 한글 데이터를 불러온다
    with h5py.File(path, 'r') as hf:
        images = np.array(hf['images'])
        labels = np.array(hf['labels'])
    

def getLenArray(img):
    # 데이터의 길이를 변수로 받는다
    len_image = len(img)


def applyRandomMorphologyEffect():
    # images 이미지들을 랜덤으로 모폴로지 연산을 수행한다
    for i in range(0, len_image):
        rNum = random.randrange(1,8)

        if(rNum == 1):
            modified_images[i] = cv2.erode(images[i],kernel,iterations = 1)
        elif(rNum == 2):
            modified_images[i] = cv2.dilate(images[i],kernel,iterations = 1)
        elif(rNum == 3):
            modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_OPEN, kernel)
        elif(rNum == 4):
            modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_GRADIENT, kernel)
        elif(rNum == 5):
            modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_CLOSE, kernel)
        elif(rNum == 6):
            modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_TOPHAT, kernel)
        elif(rNum == 7):
            modified_images[i] = cv2.morphologyEx(images[i], cv2.MORPH_BLACKHAT, kernel)


def showImage():
    # 모폴로지 연산 후와 전의 이미지를 비교해본다 
    for i in range(0,10):
        fig = plt.figure()
        fig.add_subplot(1,2,1)
        plt.imshow(images[i], cmap='gray_r') ; plt.axis('off')
        fig.add_subplot(1,2,2)
        plt.imshow(modified_images[i], cmap='gray_r') ; plt.axis('off')
        plt.show()


def shuffleData(modified_images, modified_labels):
    # 이미지들을 랜덤순서로 섞는다
    shuf = np.arange(len_image)
    np.random.shuffle(shuf)
    modified_images = modified_images[shuf]
    modified_labels = modified_labels[shuf]


def initProcess():
    # 필터 kernel을 설정한다
    kernel = np.ones((2,2), np.uint8)

    # 데이터를 받기 위해 초기설정을 한다
    modified_images = np.array(np.zeros(52998400).reshape(19600,52,52))
    modified_labels = labels

# 데이터를 19600x52x52 처럼 3차원 배열데이터로 만들어주는 코드들(사용안함)
# aa = np.dstack((images[0], images[1])).swapaxes(0,2)
# bb = np.array([images[0],images[1]])


def saveH5pyData(path, modified_images, modified_labels):
    # hdf5 파일 포맷으로 위의 데이터를 저장한다 :-)
    f = h5py.File(path,'w')
    f.create_dataset('modified_images',data=modified_images, compression_opts=9, compression='gzip')
    f.create_dataset('modified_labels',data=modified_labels, compression_opts=9, compression='gzip')
    f.close()


def loadData():
    # 저장된 데이터를 불러온다
    g = h5py.File('D:\\edward\\modified_file.hf','r')

    # 키를 확인한다
    for keys in g:
        print(keys, "---------->" , g[keys])

    mod_images = np.array(g['modified_images'])
    mlabels = np.array(g['modified_labels'])

    # Image 데이터와 Label 데이터를 numpy 데이터로 수정한다
    mod_images = mod_images.reshape(19600, 2704, )
    mod_images = mod_images / 255.

    # train Label 데이터를 [1 x 100] 의 행렬로 표현한다
    #           예를 들어 3이면 [0,0,1,0,.....,0] 과 같이 설정한다
    mod_labels  = np.array(np.zeros(274400).reshape(19600,14))
    for num in range(0,19600):
        mod_labels[num][int(mlabels[num]) - 1] = 1



filepath = 'D:\\googleDrive\\private2\\dataset_ML\\visualComputing_hangeul\\kalph_train.hf'
savepath = 'D:\\edward\\modified_file.hf'


getDataFromFile(filepath)

getLenArray(images)

initProcess()
applyRandomMorphologyEffect()

showImage()

shuffleData()

saveH5pyData(savepath, modified_images, modified_labels)

loadData()



# next_batch() 함수에 사용될 파라미터들을 수정한 후 다시 학습을 시작한다
_images = mod_images  # Image 변수 
_labels = mod_labels  # Label 변수

batch_size = 50      # 한 루프에 몇개의 (Image, Label) 데이터를 학습하는지 설정
display_step = 200   # 루프를 돌면서 화면에 표시할 빈도 설정
saver = tf.train.Saver()

for i in range(5000):
    costVal = 0.
    batch = next_batch(batch_size)
    # 20번 돌릴 때마다 결과를 확인한다
    if i % display_step == 0:
        train_accuracy = sess.run(accuracy,feed_dict={x:batch[0], y:batch[1], keep_prob:1.0})
        costVal = sess.run(cost, feed_dict={x: batch[0], y: batch[1], keep_prob:1.0})
    
        print('step', i , 'training_accuracy', train_accuracy,'cost', costVal)
        
        # 실제 학습과정 함수, dropout 50%를 토대로 학습한다
    sess.run(optimizer,feed_dict={x:batch[0],y:batch[1], keep_prob:0.5})
    # 마지막 루프에서 가중치값들을 저장한다 
    if(i == 4999):
        saver.save(sess, "d:/edward/hangeul4")
        print("[+] Done Save")


# 전부 학습이 끝나면 테스트 데이터를 넣어 정확도를 계산한다
test_accuracy = sess.run(accuracy,feed_dict={x: test_images, y: test_labels, keep_prob: 1.0})
print('test accuracy', test_accuracy)
