#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> PinkWink님 포스트에 있는 seaborn 패키지를 사용해 본 예제 코드
'''
import matplotlib.pyplot as plt
import seaborn as sns; sns.set_style("whitegrid")

# tips 데이터를 불러온다. (영수증 데이터)
tips = sns.load_dataset("tips")
tips.head()

# boxplot을 그린다
sns.boxplot(x = "day", y = "total_bill", hue= "smoker", data =tips, palette="Set3")
plt.show()


# 데이터를 점심과 저녁, 흡연여부, 성별로 구분짓는 그래프를 만든다
g = sns.FacetGrid(tips, col="time", size=5, aspect=.7)
(g.map(sns.boxplot, "sex", "total_bill", "smoker").despine(left=True).add_legend(title="smoker"))
plt.show()


# 산점도와 선형회귀 그래프를 그린다
sns.lmplot(x="total_bill", y="tip", hue="smoker", data=tips)
plt.show()


# 산점도와 선형회귀 그래프를 성별과 시간대별로 나눠서 4개로 표현한다
sns.lmplot(x="total_bill", y="tip", row="sex", col="time", data=tips, size=3)
plt.show()



#-------------------------------------------------------------

# 월별 비행기 승객의 데이터를 가져온다
flights = sns.load_dataset("flights")
flights.head()


# index를 month로 column을 year로 설정한다 (pandas의 pivot 기능!)
flights = flights.pivot("month", "year", "passengers")
flights.head()


# heatmap을 그린다
sns.heatmap(flights)


sns.heatmap(flights, annot=True, fmt="d")




#-------------------------------------------------------------
import seaborn as sns; sns.set(style="ticks", color_codes=True)

# iris 데이터를 불러온다
iris = sns.load_dataset("iris")
iris.head()

# 변수들의 상관관계 그래프를 그린다
sns.pairplot(iris, vars=["sepal_width", "sepal_length"])
plt.show()












