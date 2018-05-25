'''
	python ==> dyros, 민수씨 HMM 과제에서 데이터를 알아보기 쉽게 정리해주는 코드 for python2
'''
import numpy as np
import pandas as pd

data_pd = pd.read_csv('weather_description2.csv', keep_default_na=False)

unique = {}
counts = {}
for key in data_pd:
	unique[key], counts[key] = np.unique(data_pd[key], return_counts=True)
	sum_pd[key] = {}
	sum_pd[key] = counts[key].sum()

# dict(zip(unique['Vancouver'], counts['Vancouver']))

cnt = 0
for key in data_pd:
	cnt = 0
	for i in range(len(counts[key])):
		for j in range(1,8):
			if unique[key][i-cnt] == str(j):
				# print("{}, {}, {}".format(unique[key][i-cnt],i,j))
				counts[key][np.where(unique[key] == j)] += counts[key][i-cnt]
				counts[key] = np.delete(counts[key], np.where(unique[key] == str(j)))
				unique[key] = np.delete(unique[key], np.where(unique[key] == str(j)))
				cnt += 1



prob = []
for key in data_pd:
	print("---------------[{}]----------------".format(key))
	for i in range(len(counts[key])):
		prob.append(counts[key][i] / float(sum_pd[key]))
		print("keys [{:>3}]  {:>5.2f} [%] [{}]".format(unique[key][i], prob[i], counts[key][i]))
	print("\n")
