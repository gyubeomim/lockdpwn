#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 비주얼컴퓨팅, 프로젝트2 선형분류기를 사용해 3 class - 2 features 시스템을 분류해보는 코드
'''
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sympy import *
from sympy import solve

# Sympy 기초 세팅을 한다
x, y, z, w = symbols('x y z w')
init_printing()

#--------------------------------------------------------------
# 1. Perceptron algorithm을 사용하여 w1, w2를 구분하는 선형분류기를 작성하라. 초기 weight vector와 학습율을 다양하게 시도해 볼 것.

class Perceptron():
	def __init__(self, thresholds=0.0, eta=0.01, n_iter=10, w_ = []):
		self.thresholds = thresholds
		self.eta = eta
		self.n_iter = n_iter
                if(w_ == []):
                    self.w_ = np.zeros(3)
                else:
                    self.w_ = w_

	def fit(self,X,y):
		self.errors_ = []
                self.one = np.ones(len(X))
		self.y_ = zip(self.one, X[:,0], X[:,1])
		self.y_ = np.array(self.y_)

		for _ in range(self.n_iter):
			errors = 0
			for xi, target,i in zip(X,y,range(0,len(X))):
				update = (target - self.predict(xi))
				self.w_ += self.eta * update * self.y_[i]
				errors += int(update != 0.0)
			self.errors_.append(errors)
			print(self.w_)
		return self

	def net_input(self, X):
		return np.dot(X, self.w_[1:]) + self.w_[0]

	def predict(self, X):
		return np.where(self.net_input(X) > self.thresholds, 1, -1)


project2Data = './project2Data.dat'
names = ['x1', 'x2', 'class']
data = pd.read_csv(project2Data, header=None, names=names)

Class = data['class']
Data = np.array(data)

data1 = data[0:10]
data2 = data[10:20]
data3 = data[20:30]

class1 = data1['class']
class2 = data2['class']
class3 = data3['class']

del data['class']
del data1['class']
del data2['class']
del data3['class']

# 모든 데이터들의 산점도를 그린다
plt.plot(data1['x1'],data1['x2'],'ro',data2['x1'],data2['x2'],'bo',data3['x1'],data3['x2'],'go')
plt.grid()
plt.show()

data12 = np.vstack((data1,data2))
dataC12 = np.hstack((class1,class2))
dataC12 = np.where(dataC12 == 'w1' ,-1,1)

data13 = np.vstack((data1,data3))
dataC13 = np.hstack((class1,class3))
dataC13 = np.where(dataC13 == 'w1' ,-1,1)

initAvec = np.array([0.5,0.5,0.5])

ptron1 = Perceptron(eta = 0.1)
ptron2 = Perceptron(eta = 1)
ptron3 = Perceptron(eta = 0.5, w_ = initAvec)

ptron1.fit(data12, dataC12)
print("\n")
ptron2.fit(data12, dataC12)
print("\n")
ptron3.fit(data12, dataC12)
print("\n")

def frange(x, y, jump):
  while x < y:
    yield x
    x += jump


yy = []
for i in frange(-10,10,0.1):
    yy.append(0.8879*i  - 1.1206)

xx = np.linspace(-10,10,201)
plt.title('[w1, w2] eta=0.1, a=[0,0,0]',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yy) 
plt.plot(data1['x1'],data1['x2'],'ro',data2['x1'],data2['x2'],'bo')
plt.legend(['perceptron','w1','w2'])
plt.grid()
plt.show()


yyy = []
for i in frange(-10,10,0.1):
    yyy.append(0.8879*i  - 1.1206)

xx = np.linspace(-10,10,201)
plt.title('[w1, w2] eta=1, a=[0,0,0]',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yyy) 
plt.plot(data1['x1'],data1['x2'],'ro',data2['x1'],data2['x2'],'bo')
plt.legend(['perceptron','w1','w2'])
plt.grid()
plt.show()



yyy2 = []
for i in frange(-10,10,0.1):
    yyy2.append(0.83319*i - 1.5583)

xx = np.linspace(-10,10,201)
plt.title('[w1, w2] eta=0.5, a = [.5,.5,.5]',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yyy2) 
plt.plot(data1['x1'],data1['x2'],'ro',data2['x1'],data2['x2'],'bo')
plt.legend(['perceptron','w1','w2'])
plt.grid()
plt.show()





#--------------------------------------------------------------
# 2. Batch relaxation algorithm을 사용하여 w1과 w3를 구분하는 선형분류기를 작성하라. Margin b를 0.1과 0.5, 초기 weight vector를 (0, 0, 0)로 하였을 경우의 결과들을 보여라.


class BatchRelaxationWithMargin():
	def __init__(self, thresholds=0.0, eta=0.01, n_iter=10, margin = 0.1):
		self.thresholds = thresholds
		self.eta = eta
		self.n_iter = n_iter
		self.margin = margin

	def fit(self,X,y):
		self.w_ = np.zeros(1 + X.shape[1])
		self.errors_ = []
                self.one = np.ones(len(X))
		self.y_ = zip(self.one, X[:,0], X[:,1])
		self.y_ = np.array(self.y_)

		for _ in range(self.n_iter):
			errors = 0
			for xi, target,i in zip(X,y,range(0,len(X))):
				update = (target - self.predict(xi))
				if(update != 0):
					delta = (update * self.y_[i] * (self.margin - self.w_ * update * self.y_[i] )) / ((np.linalg.norm(update * self.y_[i]))**2)
					self.w_ += delta * self.eta
				errors += int(update != 0.0)
			self.errors_.append(errors)
			print(self.w_)
		return self

	def net_input(self, X):
		return np.dot(X, self.w_[1:]) + self.w_[0]

	def predict(self, X):
		return np.where(self.net_input(X) > self.thresholds, 1, -1)


bat = BatchRelaxationWithMargin(eta = 0.1, margin = 0.1)
bat.fit(data13, dataC13)
print("\n")
bat2 = BatchRelaxationWithMargin(eta = 0.5, margin = 0.5)
bat2.fit(data13, dataC13)
print("\n")
bat3 = BatchRelaxationWithMargin(eta = 0.2, margin = 0.1)
bat3.fit(data13, dataC13)

yy2 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy2.append(0.1668*i + 1.119)

plt.title('[w1, w3] eta=0.1, margin = 0.1',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yy2) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.legend(['Batch Relaxation with margin','w1','w3'])
plt.grid()
plt.show()


yy3 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy3.append(0.6091*i + 0.8582)

plt.title('[w1, w3] eta=0.5, margin = 0.5',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yy3) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.legend(['Batch Relaxation with margin','w1','w3'])
plt.grid()
plt.show()


yy7 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy7.append(0.3437*i + 0.6732)

plt.title('[w1, w3] eta=0.2, margin = 0.1',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yy7) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.legend(['Batch Relaxation with margin','w1','w3'])
plt.grid()
plt.show()










#--------------------------------------------------------------
# 3. Widrow-Hoff (LMS) algorithm을 사용하여 w1과 w3를 구분하는 선형분류기를 작성하라. 다양한 initial weight vector a, margin vector b, threshold, learning rate를 시도해 볼 것.


class WidrowHoff():
	def __init__(self, thresholds=0.0, eta=0.01, n_iter=10, b_ = 0.1, w_ = []):
		self.thresholds = thresholds
		self.eta = eta
		self.n_iter = n_iter
		self.b_ = b_
                if(w_ == []):
                    self.w_ = np.zeros(3)
                else:
                    self.w_ = w_

	def fit(self,X,y):
		self.errors_ = []
                self.one = np.ones(len(X))
		self.y_ = zip(self.one, X[:,0], X[:,1])
		self.y_ = np.array(self.y_)

		for _ in range(self.n_iter):
			errors = 0
			for xi, target, i in zip(X, y, range(0, len(X))):
				update = (target - self.predict(xi))
				if(update != 0):
					delta = np.dot(update * self.y_[i], self.b_ - np.dot(update * self.y_[i], self.w_.T)) / self.n_iter
					self.w_ += delta * self.eta
				errors += int(update != 0.0)
			self.errors_.append(errors)
			print(self.w_)
		return self

	def net_input(self, X):
		return np.dot(X, self.w_[1:]) + self.w_[0]

	def predict(self, X):
		return np.where(self.net_input(X) > self.thresholds, 1, -1)


initAvec = np.array([0.5,0.5,0.5])

wid = WidrowHoff(eta = 0.1, b_ = 0.001, n_iter = 10)
wid.fit(data13,dataC13)
print("\n")
wid2 = WidrowHoff(eta = 0.001, b_ = 0.1, n_iter = 10)
wid2.fit(data13,dataC13)
print("\n")
wid3 = WidrowHoff(eta = 0.1, b_ = 0.1, n_iter = 10, w_ = initAvec)
wid3.fit(data13,dataC13)




yy4 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy4.append(1.0244*i + 1.3034)


plt.title('[w1, w3] : eta=0.1 , a=[0,0,0], b=0.001',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yy4) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.legend(['widrowHoff','w1','w3'])
plt.grid()
plt.show()



yy5 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy5.append(0.9624*i + 1.2388)

plt.title('[w1, w3] : eta=0.1 , a=[.5,.5,.5], b=0.1',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yy5) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.legend(['widrowHoff','w1','w3'])
plt.grid()
plt.show()


yy6 = []
xx = np.linspace(-10,10,201)
for i in frange(-10,10,0.1):
    yy6.append(0.5019*i + 0.6556)

plt.title('[w1, w3] : eta=0.001 , a=[0,0,0], b=0.1',fontsize=16)
plt.xlabel('x1')
plt.ylabel('x2')
plt.plot(xx,yy6) 
plt.plot(data1['x1'],data1['x2'],'ro',data3['x1'],data3['x2'],'go')
plt.legend(['widrowHoff','w1','w3'])
plt.grid()
plt.show()

