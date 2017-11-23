confint.1 <- function(x, alpha = .05, two.tailed = TRUE) {
	cat("\t",(1-alpha)*100,"percent confidence interval","\n")
	cat("Mean:",mean(x),"\n")
	cat("Sample size:",length(x),"\n")
	cat("Std. Deviation:",sd(x),"\n")
	df <- length(x) - 1
	stderr <- sd(x)/sqrt(length(x))
	cat("Standard error of the mean:",stderr,"\n")
	conflevel <- 1 - alpha/2
	if (two.tailed == FALSE) {
		conflevel <- 1 - alpha
		}
	tcrit <- qt(conflevel, df)
	margin <- stderr * tcrit
	LL <- mean(x) - margin
	UL <- mean(x) + margin
	if (two.tailed == FALSE) {
		cat("You are doing a one-tailed test.","\n")
		cat("If your test is left-tailed,","\n")
		cat("the lower bound is negative infinity.","\n")
		cat("If your test is right-tailed,","\n")
		cat("the upper bound is positive infinity.","\n")
		cat("Either add the margin",margin,"to or subract it from","\n")
		cat("the sample mean as appropriate.","\n")
		cat("For a left-tailed test, the upper bound is",LL,"\n")
		cat("For a right-tailed test, the lower bound is",UL,"\n")
		}
	cat("upper bound:",LL,"\n")
	cat("lower bound:",UL,"\n")
}