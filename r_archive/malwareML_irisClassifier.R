head(iris)
str(iris)

setosa <- iris[iris$Species == 'setosa',]
versicolor <- iris[iris$Species == 'versicolor',]
virginica <- iris[iris$Species == 'virginica',]

# 데이터를 20% 와 80%로 2개로분할한다
ind <- sample(2, nrow(iris), replace=TRUE, prob=c(0.8,0.2))
trainData <- iris[ind==1,]
testData <- iris[ind==2,]

install.packages("rpart")
install.packages("rpart.plot")
install.packages("e1071")
installed.packages("caret")
library(rpart)
library(rpart.plot)
library(e1071)
library(caret)

fit <- rpart(Species ~ . , data=trainData)
rpart.plot(fit)

pred <- predict(fit, testData[,1:4], type="class")
confusionMatrix(pred, testData$Species)
