'''
	 R ==> 머신러닝처음, Rule Based Classification을 적용해 중고등학생의 보충교육시간을 적절하게 선택해보는 예제 코드
							적용도 : 확률
							정확도 : 조건부확률
							가능도비율 : 관찰도수 / 기대도수
'''
test <- read.csv("rule.csv", header = T)

r1 <- NROW(subset(test, 효과 == "YES")) / NROW(test)
r2 <- NROW(subset(test, 효과 == "NO")) / NROW(test)

# 가능도비율, 정확도, 적용도를 구해주는 함수
like_cov_acc <- function(cond, res)
{
	f1 <- NROW(subset(cond, 효과 == "YES"))
	f2 <- NROW(subset(cond, 효과 == "NO"))

	e1 <- NROW(cond) * r1
	e2 <- NROW(cond) * r2

	like <- 2 * (f1 * log(f1/e1) + f2 * log(f2/e2))

	# 적용도 coverage와 정확도 accuracy
	cove <- NROW(cond) / NROW(test)
	acc <- NROW(subset(cond, 효과 == res)) / NROW(cond)

	cat("적용도는", cove, "입니다\n")
	cat("정확도는", acc, "입니다\n")
	cat("기능도비율은", like, "입니다\n")
}

# RULE 1
cond1 <- subset(test, 과목 == "수학" & 수업일 == "주말")
res1 = "NO"
like_cov_acc(cond1, res1)


# RULE 2
cond2 <- subset(test, 과목 == "과학")
res2 <- "NO"
like_cov_acc(cond2, res2)


# RULE 3
cond3 <- subset(test, (과목 == "과학" | 과목 == "수학") & 수업시간대 == "저녁" & (class == "A" | class == "B"))
res3 <- "NO"
like_cov_acc(cond3, res3)


# RULE 4
cond4 <- subset(test, (과목 == "국어" | 과목 == "영어") & (class == "A" | class == "B"))
res4 <- "NO"
like_cov_acc(cond4, res4)




