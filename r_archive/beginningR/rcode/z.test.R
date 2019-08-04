z.test <-
function(x, mu, sigma, n, alpha = .05){
  meanx <- mean(x)
  stdev <- sd(x)
  sterr <- sigma/sqrt(n)
  n <- length(x)
  z <- (meanx - mu)/(sigma/sqrt(n))
  zcrit <- abs(qnorm(alpha/2))
  pvalue <- 1-pnorm(abs(z))
  meandiff <- meanx - mu
  ll <- meandiff - (zcrit * sterr)
  ul <- meandiff + (zcrit * sterr)
  cat("\t","One-sample z test","\n","\n")
  cat("test value:", mu, "\n")
  cat("sample mean:", meanx,"\n")
  cat("std. deviation:", stdev,"\n")
  cat("sample size",n,"\n")
  cat("std. error:",sterr,"\n")
  cat("calculated z:", z, "\n")
  cat("critical value of z:", zcrit,"\n")
  cat("p value:", pvalue, "\n","\n")
  cat("mean difference:",meandiff,"\n")
  cat((1-alpha) * 100,"% confidence interval:",ll,ul,"\n")
}
