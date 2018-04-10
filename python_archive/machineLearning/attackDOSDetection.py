#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
	python ==> 해킹 & 보안 실습에 사용한 예제코드
'''

%matplotlib inline
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv('/home/stud/Desktop/kddcup_subset.csv')

df['V23'].head(10)
df.info()
df.describe()

# 데이터를 normal : 0, smuff : 1과 같이 설정한 후 쪼갠다

df.ix[df['V42'] == 'normal.', 'V42'] = 0
df.ix[df['V42'] != 0 , 'V42'] = 1


normal = df.loc[df.V42 ==0]
abnormal = df.loc[df.V42 != 0]

# 데이터프레임을 행렬로 바꾼다. 반드시 할 필요는 없지만 아래 해석코드에서 행렬을 사용하기 때문에 변환
df.as_matrix()

# 학습 80% 테스트 20% 로 데이터를 나눈다
x_train_n, x_test_n = np.split(normal, [int(.8 * len(normal))])
x_train_a, x_test_a = np.split(abnormal, [int(.8 * len(abnormal))])

# 쪼갠 데이터를 학습용끼리, 테스트용끼리 묶는다
x_train = np.concatenate([x_train_n, x_train_a])
x_test = np.concatenate([x_test_n, x_test_a])

# 학습용 데이터를 plot
plt.figure()
plt.plot(x_train[:,23], x_train[:,24],"bx")
plt.xlabel("Feature 23")
plt.ylabel("Feature 24")
plt.show()



# 레이블 데이터만 따로 뽑아준다
y_train = x_train[:,42]
y_test = x_test[:,42]

# 컬럼 23,24의 데이터만 따로 추출한다
x_train = np.column_stack((x_train[:,23], x_train[:,24]))
x_test = np.column_stack((x_test[:,23], x_test[:,24]))

# 데이터를 np.array 형식으로 설정한다
x_train = np.array(x_train, dtype="int")
y_test = np.array(y_test, dtype="int")



from scipy.stats import multivariate_normal
from sklearn.metrics import f1_score  # recall , precision을 동시에 볼 수 있는 방법
from sklearn import mixture

def feature_normal(dataset):
    mu = np.mean(dataset, axis= 0)
    sigma = np.std(dataset, axis=0)
    return (dataset - mu) / sigma

# 가우시안의 평균 분산 값을 리턴하는 함수
def estimateGaussian(dataset):
    mu = np.mean(dataset, axis=0)
    sigma = np.cov(dataset.T)
    return mu, sigma

# 실제 가우시안 그림을 만들어주는 함수
def multivariateGaussian(dataset, mu, sigma):
    p = multivariate_normal(mean=mu, cov=sigma)
    return p.pdf(dataset)

# 탐지의 기준이 되는 범위를 자동으로 선택해주는 함수
# f1_score를 사용해서 최적의 경계를 찾아준다
def selectThresholdByCV(probs, gt):
    best_epsilon = 0
    best_f1 = 0
    f = 0
    stepsize = (max(probs) - min(probs)) / 10000;  # 10000은 하이퍼파라미터이다. 바꿔서 시도도 해보면 좋다
    epsilons = np.arange(min(probs), max(probs), stepsize)
    
    for epsilon in np.nditer(epsilons):
        predictions = (probs < epsilon)
        f = f1_score(gt, predictions, average = "binary")
        if f > best_f1:
            best_f1 = f
            best_epsilon = epsilon
    return best_f1, best_epsilon


mu, sigma = estimateGaussian(x_train)
p = multivariateGaussian(x_train, mu, sigma)
p_t = multivariateGaussian(x_test, mu, sigma)

fscore, ep = selectThresholdByCV(p_t, y_test)

outliers = np.asarray(np.where( p < ep))

plt.figure()
plt.plot(x_train[:,0], x_train[:,1], "bx")
plt.plot(x_train[outliers, 0], x_train[outliers, 1], "ro")
plt.show()
