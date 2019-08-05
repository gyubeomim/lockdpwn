

RegModel.1 <- lm(height~weight, data=males)
summary(RegModel.1)
Anova(RegModel.1, type="II")

