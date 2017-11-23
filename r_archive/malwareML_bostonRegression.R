data(Boston, package = "MASS")
names(Boston)
head(Boston)
attach(Boston)

corr <- cor(Boston)

install.packages("corrplot")
library(corrplot)

# 파란색이 상관관계 높은것, 빨간색이 낮은 것
corrplot(corr, order = "hclust")

# 데이터를 20%, 80%로 2개로 분할한다
ind <- sample(2, nrow(Boston), replace = TRUE, prob = c(0.8, 0.2))
trainData <- Boston[ind == 1, ]
testData <- Boston[ind == 2, ]

# 트레이닝 데이터로 모델을 학습시킨다
fit <- lm(medv ~., data = trainData)
fit2 <- lm(medv ~ rm, data = trainData)

# 학습시킨 모델로 테스트데이터를 예측해본다
pred <- predict(fit, testData[, 1:13])

plot(pred, testData[, 14], ylim = c(0, 50), xlim = c(0, 50))
abline(0, 1)





#
