#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 비주얼컴퓨팅수업, Iris 벚꽃의 3개의 종류를 GaussianNaiveBayes 알고리즘와 SVM 알고리즘을 통해 분류해보는 프로젝트
									3개 class의 4개의 attribute들을 학습해서
									40개 학습해서 10개의 테스트 데이터를 학습해본다
									confusion_matrix도 작성해본다
'''
import pandas
from pandas.tools.plotting import scatter_matrix
import matplotlib.pyplot as plt

from sklearn import model_selection
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC

names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'class']

# 훈련용 데이터 설정
train_filepath = "./Iris_train.dat"
train_dataset = pandas.read_csv(train_filepath, names = names)
# 테스트용 데이터 설정 
test_filepath = "./Iris_test.dat"
test_dataset = pandas.read_csv(test_filepath, names = names)

array = train_dataset.values
X = array[:,0:4]
Y = array[:,4]

array2 = test_dataset.values
X_test = array2[:,0:4]
Y_test = array2[:,4]

#print(train_dataset.shape)
#print(train_dataset.head(20))
#print(train_dataset.describe())
#print(train_dataset.groupby('class').size())

#train_dataset.plot(kind='box', subplots=True, layout=(2,2), sharex=False, sharey=False)
#plt.show()
#train_dataset.hist()
#plt.show()

#scatter_matrix(train_dataset)
#plt.show()

seed=7
scoring = 'accuracy'

models = []
models.append(('Naive Bayes', GaussianNB()))
models.append(('SVM',SVC()))

results = []
names = []

# Naive Bayes와 SVM 알고리즘의 성능을 평가한다
for name,model in models:
	kfold = model_selection.KFold(n_splits=10, random_state=seed)
	cv_results = model_selection.cross_val_score(model, X, Y, cv=kfold, scoring=scoring)
	results.append(cv_results)
	names.append(name)
	msg = "%s: %f (%f)" % (name, cv_results.mean(), cv_results.std())
	print(msg)

# 성능을 평가한 다음 도식한다
fig = plt.figure()
fig.suptitle('Algorithm Comparison')
ax = fig.add_subplot(111)
plt.boxplot(results)
ax.set_xticklabels(names)
plt.show()

# Naive Bayes를 선택하고 정확도와 Confusion Matrix를 설정한다
NB = GaussianNB()
NB.fit(X, Y)
predictions = NB.predict(X_test)
print(accuracy_score(Y_test, predictions))
print(confusion_matrix(Y_test, predictions))
print(classification_report(Y_test, predictions))


