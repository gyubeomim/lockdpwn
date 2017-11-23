#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 비주얼컴퓨팅수업, 프로젝트1에 사용한 Iris를 4개의 특성, 2개의 특성으로 분류기를 만들어본 코드
'''
import pandas
import numpy as np
import matplotlib.pyplot as plt
from sympy import *
from sympy import solve
from mpl_toolkits.mplot3d import Axes3D

# Sympy 기초 세팅을 한다
x, y, z, w = symbols('x y z w')
init_printing()

# 컬럼의 이름을 입력한다
names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'class']

# 훈련용 데이터 설정
train_filepath = "./Iris_train.dat"
train_dataset = pandas.read_csv(train_filepath, names = names)

# 테스트용 데이터 설정 
test_filepath = "./Iris_test.dat"
test_dataset = pandas.read_csv(test_filepath, names = names)

testClass = test_dataset['class']
del test_dataset['class']
testData = np.array(test_dataset)
testData2 = testData[:,0:2]

class1 = train_dataset[0:40]
class2 = train_dataset[40:80]
class3 = train_dataset[80:120]

class15 = class1['class']
class25 = class2['class']
class35 = class3['class']

del class1['class']
del class2['class']
del class3['class']


# ================================================================================
# a. Assume that each class has a normal distribution, and use the training data to estimate the mean and covariance of each class.
# ================================================================================
class1.describe()
class2.describe()
class3.describe()

class11 = np.array(class1)
class22 = np.array(class2)
class33 = np.array(class3)

meanvec1 = np.matrix('4.9975; 3.4175; 1.4425; 0.2525')
meanvec2 = np.matrix('5.99; 2.7775; 4.31; 1.3325')
meanvec3 = np.matrix('6.61; 2.97; 5.5575; 2.03')

cov1 = np.cov(class11.T)
cov2 = np.cov(class22.T)
cov3 = np.cov(class33.T)

icov1 = np.linalg.inv(cov1)
icov2 = np.linalg.inv(cov2)
icov3 = np.linalg.inv(cov3)




# ================================================================================
# b. Determine the decision boundaries
# ================================================================================
xvec = Matrix([x,y,z,w]).T

# BAYES.pdf 61페이지에 있는 CASE 3의 공식을 사용해서 결정함수들을 구한다 good!!
d1First = -0.5 * xvec * icov1 * xvec.T
d1Second = xvec * icov1 * meanvec1
d1Third = -0.5 * meanvec1.T * icov1 * meanvec1 -0.5 * log(np.linalg.det(cov1))

d2First = -0.5 * xvec * icov2 * xvec.T
d2Second = xvec * icov2 * meanvec2
d2Third = -0.5 * meanvec2.T * icov2 * meanvec2 -0.5 * log(np.linalg.det(cov2))

d3First = -0.5 * xvec * icov3 * xvec.T
d3Second = xvec * icov3 * meanvec3
d3Third = -0.5 * meanvec3.T * icov3 * meanvec3 -0.5 * log(np.linalg.det(cov3))

# 결정함수 d1,d2,d3를 구하고 경계평면인 d12,d23,d13을 구한다
d1 = d1First + d1Second + d1Third
d2 = d2First + d2Second + d2Third
d3 = d3First + d3Second + d3Third

d12 = d1 - d2
d23 = d2 - d3
d13 = d1 - d3

def substitute(func,li):
    print(func.subs({x:li[0],y:li[1],z:li[2],w:li[3]}))
    return func.subs({x:li[0],y:li[1],z:li[2],w:li[3]})

# 각각 d12, d23, d13의 정확도를 검정한다.
# test 데이터를 넣어봐서 정확히 분류하는지 검정한다
value1 = []; value2 = []; value3 = []
value4 = []; value5 = []; value6 = []
value7 = []; value8 = []; value9 = []

for i in range(0,len(testData)):
    if(i < 10):
        value1.append(substitute(d12,testData[i]))
    elif(i < 20 and i >= 10):
        value2.append(substitute(d12,testData[i]))
    elif(i < len(testData) and i >= 20):
        value3.append(substitute(d12,testData[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value1 = np.array(value1)
value2 = np.array(value2)
value3 = np.array(value3)

print("<%.3f, %.3f, %.3f>\n" % (value1.mean(),value2.mean(),value3.mean()))

for i in range(0,len(testData)):
    if(i < 10):
        value4.append(substitute(d23,testData[i]))
    elif(i < 20 and i >= 10):
        value5.append(substitute(d23,testData[i]))
    elif(i < len(testData) and i >= 20):
        value6.append(substitute(d23,testData[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value4 = np.array(value4)
value5 = np.array(value5)
value6 = np.array(value6)
print("<%.3f, %.3f, %.3f>\n" % (value4.mean(),value5.mean(),value6.mean()))

for i in range(0,len(testData)):
    if(i < 10):
        value7.append(substitute(d13,testData[i]))
    elif(i < 20 and i >= 10):
        value8.append(substitute(d13,testData[i]))
    elif(i < len(testData) and i >= 20):
        value9.append(substitute(d13,testData[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value7 = np.array(value7)
value8 = np.array(value8)
value9 = np.array(value9)

print("<%.3f, %.3f, %.3f>\n" % (value7.mean(),value8.mean(),value9.mean()))


# ================================================================================
# c. Classify the testing data set and construct the confusion matrix.
# ================================================================================

confusionMatrix = Matrix([[10,0,0],[0,10,0],[0,0,10]])










# ================================================================================
# 2) In this problem we will use the first 2 features of the Iris data.
# a. Plot the training data samples (each class should be assigned a different symbol).
# ================================================================================

c1 = class11[:,0:2]
c2 = class22[:,0:2]
c3 = class33[:,0:2]

c1x = class11[:,0]
c1y =class11[:,1]

c2x = class22[:,0]
c2y =class22[:,1]

c3x = class33[:,0]
c3y =class33[:,1]


plt.title('Train Data set for Iris',fontsize=16)
plt.xlabel('Sepal-Length')
plt.ylabel('Sepal-Width')
plt.plot(c1x,c1y,'bo',c2x,c2y,'ro',c3x,c3y,'go')
plt.legend(['Iris-setosa','Iris-versicolor','Iris-virginica'])
plt.grid()
plt.show()




# ================================================================================
# b. Estimate the mean and covariance of each class.
# ================================================================================

print("class1 mean : [%.3f, %.3f]" % (c1x.mean(),c1y.mean()) + "\n       std :[%.3f, %.3f]" % (c1x.std(), c1y.std()))
print("class2 mean : [%.3f, %.3f]" % (c2x.mean(),c2y.mean()) + "\n       std :[%.3f, %.3f]" % (c2x.std(), c2y.std()))
print("class3 mean : [%.3f, %.3f]" % (c3x.mean(),c3y.mean()) + "\n       std :[%.3f, %.3f]" % (c3x.std(), c3y.std()))











# ================================================================================
# c. Plot the means and the contours for which the Mahalanobis distance = 2. (same plot as in (a) )
# ================================================================================

xvec2 = Matrix([x,y]).T

meanv1 = meanvec1[0:2,:].T
meanv2 = meanvec2[0:2,:].T
meanv3 = meanvec3[0:2,:].T
c1cov = np.cov(c1x, c1y)
c2cov = np.cov(c2x, c2y)
c3cov = np.cov(c3x, c3y)

invc1cov = np.linalg.inv(c1cov)
invc2cov = np.linalg.inv(c2cov)
invc3cov = np.linalg.inv(c3cov)

ym11 = [] ; ym12 = []
ym21 = [] ; ym22 = []
ym31 = [] ; ym32 = []
xm1 = np.linspace(4.,8.,41)

m1 = (xvec2 - meanv1)* invc1cov * (xvec2 - meanv1).T
m2 = (xvec2 - meanv2)* invc2cov * (xvec2 - meanv2).T
m3 = (xvec2 - meanv3)* invc3cov * (xvec2 - meanv3).T

def frange(x, y, jump):
  while x < y:
    yield x
    x += jump

for i in frange(4.,8.,0.1):
    ym11.append(re(solve((m1[0] -2).subs({x:i}) ,y)[0]))
    ym12.append(re(solve((m1[0] -2).subs({x:i}) ,y)[1]))
    ym21.append(re(solve((m2[0] -2).subs({x:i}) ,y)[0]))
    ym22.append(re(solve((m2[0] -2).subs({x:i}) ,y)[1]))
    ym31.append(re(solve((m3[0] -2).subs({x:i}) ,y)[0]))
    ym32.append(re(solve((m3[0] -2).subs({x:i}) ,y)[1]))


plt.title('Train Data set for Iris with Mahalanobis Dist = 2',fontsize=16)
plt.xlabel('Sepal-Length')
plt.ylabel('Sepal-Width')
plt.plot(c1x,c1y,'bo',c2x,c2y,'ro',c3x,c3y,'go')
plt.legend(['Iris-setosa','Iris-versicolor','Iris-virginica'])
plt.plot(meanv1.item(0),meanv1.item(1), 'cD', meanv2.item(0), meanv2.item(1),'cD', meanv3.item(0), meanv3.item(1),'cD')
plt.plot(xm1,ym11,'b--',xm1,ym12,'b--',xm1,ym21,'r--',xm1,ym22,'r--',xm1,ym31,'g--',xm1,ym32,'g--')
plt.grid()
plt.show()




#-----------------------------------------------------------------------------
# 이건 안해도 되는건데 했다. 마할라노비스 등고선
'''
xx = np.linspace(4,8,25)
yy = np.linspace(2,5,25)

XX,YY = np.meshgrid(xx,yy)
XY = np.stack((XX,YY)).T

zz1 = [[0]*25 for i in range(25)]
zz2 = [[0]*25 for i in range(25)]
zz3 = [[0]*25 for i in range(25)]

# 마할라노비스 거리를 구하는 공식
for i in range(0,25):
    for j in range(0,25):
        zz1[i][j] = ((XY[i][j][:,]-meanv1) * invc1cov * (XY[i][j][:,] - meanv1).T).item(0)
        zz2[i][j] = ((XY[i][j][:,]-meanv2) * invc2cov * (XY[i][j][:,] - meanv2).T).item(0)
        zz3[i][j] = ((XY[i][j][:,]-meanv3) * invc3cov * (XY[i][j][:,] - meanv3).T).item(0)

zz1 = np.array(zz1)
zz2 = np.array(zz2)
zz3 = np.array(zz3)

# 마할라노비스 등고선
plt.contour(XX,YY,zz1) ; plt.show()
plt.contour(XX,YY,zz2) ; plt.show()
plt.contour(XX,YY,zz3) ; plt.show()

# 마할라노비스 등고선 3차원 형상 
fig = plt.figure()
fig2 = plt.figure()
fig3 = plt.figure()
ax = Axes3D(fig)
ax2 = Axes3D(fig2)
ax3 = Axes3D(fig3)
ax.plot_surface(XX, YY, zz1, rstride=1, cstride=1, cmap='hot')
ax2.plot_surface(XX, YY, zz2, rstride=1, cstride=1, cmap='hot')
ax3.plot_surface(XX, YY, zz3, rstride=1, cstride=1, cmap='hot')
plt.show()
'''
#-----------------------------------------------------------------------------




# ================================================================================
# d. Determine the decision boundaries and plot them (same plot as in (a))
# ===============================================================================

# 각 클래스의 공분산을 구한다
cov11 = np.cov(c1.T)
cov22 = np.cov(c2.T)
cov33 = np.cov(c3.T)

# 공분산의 역함수를 구한다
icov11 = np.linalg.inv(cov11)
icov22 = np.linalg.inv(cov22)
icov33 = np.linalg.inv(cov33)

# 3개 클래스의 경계함수를 구해서 e1,e2,e3에 넣는다 
# 그 다음 서로의 경계평면인 e12, e23, e13을 구한다
e1First = -0.5 * xvec2 * icov11 * xvec2.T
e1Second = (icov11 * meanv1.T).T * xvec2.T
e1Third = -0.5 * meanv1 * icov11 * meanv1.T -0.5*log(np.linalg.det(cov11))

e2First = -0.5 * xvec2 * icov22 * xvec2.T
e2Second = (icov22 * meanv2.T).T * xvec2.T
e2Third = -0.5 * meanv2 * icov22 * meanv2.T -0.5*log(np.linalg.det(cov22))

e3First = -0.5 * xvec2 * icov33 * xvec2.T
e3Second = (icov33 * meanv3.T).T * xvec2.T
e3Third = -0.5 * meanv3 * icov33 * meanv3.T -0.5*log(np.linalg.det(cov33))

e1 = e1First + e1Second + e1Third
e2 = e2First + e2Second + e2Third
e3 = e3First + e3Second + e3Third

e12 = e1 - e2
e23 = e2 - e3
e13 = e1 - e3

# 2개의 변수만을 고려하는 함수를 만든다
def substitute2(func,li):
    print(func.subs({x:li[0],y:li[1]}))
    return func.subs({x:li[0],y:li[1]})


# 각각 e12, e23, e13의 정확도를 검정한다.
# test 데이터를 넣어봐서 정확히 분류하는지 검정한다
value1 = []; value2 = []; value3 = []
value4 = []; value5 = []; value6 = []
value7 = []; value8 = []; value9 = []

for i in range(0,len(testData2)):
    if(i < 10):
        value1.append(substitute2(e12, testData2[i]))
    elif(i < 20 and i >= 10):
        value2.append(substitute2(e12, testData2[i]))
    elif(i < len(testData2) and i >= 20):
        value3.append(substitute2(e12, testData2[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value1 = np.array(value1)
value2 = np.array(value2)
value3 = np.array(value3)
print("<%.3f, %.3f, %.3f>\n" % (value1.mean(),value2.mean(),value3.mean()))

for i in range(0,len(testData2)):
    if(i < 10):
        value4.append(substitute2(e23,testData2[i]))
    elif(i < 20 and i >= 10):
        value5.append(substitute2(e23,testData2[i]))
    elif(i < len(testData2) and i >= 20):
        value6.append(substitute2(e23,testData2[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value4 = np.array(value4)
value5 = np.array(value5)
value6 = np.array(value6)
print("<%.3f, %.3f, %.3f>\n" % (value4.mean(),value5.mean(),value6.mean()))

for i in range(0,len(testData2)):
    if(i < 10):
        value7.append(substitute2(e13,testData2[i]))
    elif(i < 20 and i >= 10):
        value8.append(substitute2(e13,testData2[i]))
    elif(i < len(testData2) and i >= 20):
        value9.append(substitute2(e13,testData2[i]))

    if(i % 10 == 9 and i != 0):
        print('\n')

value7 = np.array(value7)
value8 = np.array(value8)
value9 = np.array(value9)
print("<%.3f, %.3f, %.3f>\n" % (value7.mean(),value8.mean(),value9.mean()))


# e12, e13, e23 방정식의 해를 (x,y)로 구해서 y1,y2,y3에 넣는다
y1 = []
y2 = []
y3 = []
x1 = np.linspace(4,8,41)



def makeLine(func, a,b):
    return func.subs({x:a,y:b})

# 값 뽑아오기 한 번 힘드네 ㅡㅡ
for i in frange(4.,8.,0.1):
    y1.append(re(solve(e12.subs({x:i}),y)[0][0]))
    y2.append(re(solve(e23.subs({x:i}),y)[0][0]))
    y3.append(re(solve(e13.subs({x:i}),y)[0][0]))


plt.title('Train Data set for Iris with plane',fontsize=16)
plt.xlabel('Sepal-Length')
plt.ylabel('Sepal-Width')
plt.plot(c1x,c1y,'bo',c2x,c2y,'ro',c3x,c3y,'go')
plt.legend(['Iris-setosa','Iris-versicolor','Iris-virginica'])
plt.plot(x1,y1,'b',x1,y2,'r',x1,y3,'g')
plt.grid()
plt.xlim(4,8)
plt.ylim(2,5)
plt.show()





# ================================================================================
# e. Add the test data set to the plot. (correctly classified points, misclassified points, and points from different classes should be assigned different symbols).
# ================================================================================

t1x = testData2[0:10,0]
t1y = testData2[0:10,1]
t2x = testData2[10:20,0]
t2y = testData2[10:20,1]
t3x = testData2[20:30,0]
t3y = testData2[20:30,1]


plt.title('Test Data set for Iris',fontsize=16)
plt.xlabel('Sepal-Length')
plt.ylabel('Sepal-Width')
plt.plot(t1x,t1y,'bo',t2x,t2y,'ro',t3x,t3y,'go')
plt.legend(['Iris-setosa','Iris-versicolor','Iris-virginica'])
plt.plot(c1x,c1y,'b,',c2x,c2y,'r,',c3x,c3y,'g,')
plt.grid()
plt.xlim(4,8)
plt.ylim(2,5)
plt.show()


plt.title('Test Data set for Iris with plane',fontsize=16)
plt.xlabel('Sepal-Length')
plt.ylabel('Sepal-Width')
plt.plot(t1x,t1y,'bo',t2x,t2y,'ro',t3x,t3y,'go')
plt.legend(['Iris-setosa','Iris-versicolor','Iris-virginica'])
plt.plot(c1x,c1y,'b,',c2x,c2y,'r,',c3x,c3y,'g,')
plt.plot(x1,y1,'b',x1,y2,'r',x1,y22,'r',x1,y3,'g')
plt.grid()
plt.xlim(4,8)
plt.ylim(2,5)
plt.show()




# ================================================================================
# f. Classify the test data set (using discriminant functions and using the graph) and construct the confusion matrix. Compare the results with the previous problem.
# ================================================================================

confusionMatrix2 = Matrix([[10,0,0],[0,8,2],[0,4,6]])








