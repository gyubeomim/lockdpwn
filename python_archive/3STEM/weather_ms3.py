'''
	python ==> dyros, 민수씨 HMM 과제에서 데이터를 알아보기 쉽게 정리해주는 코드 for python3
'''
import numpy as np
import pandas as pd

data_pd = pd.read_csv('weather_description2.csv', keep_default_na=False, dtype=object)

unique = {}
counts = {}
for key in data_pd:
	unique[key], counts[key] = np.unique(data_pd[key], return_counts=True)
	sum_pd[key] = {}
	sum_pd[key] = counts[key].sum()


prob = []
for key in data_pd:
	print("---------------[{}]----------------".format(key))
	for i in range(len(counts[key])):
		prob.append(counts[key][i] / float(sum_pd[key]))
		print("keys [{:>3}]  {:>5.2f} [%] [{}]".format(unique[key][i], prob[i], counts[key][i]))
	print("\n")
