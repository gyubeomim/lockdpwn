confi.var <- function(x,n,alpha = .05){
  chisqL <- qchisq(alpha/2, n-1)
  chisqR <- qchisq(1 - alpha/2, n-1)
  sampvar <- var(x)
  lower <- ((n - 1) * sampvar)/chisqR
  upper <- ((n - 1) * sampvar)/chisqL
  cat("\t",1 - alpha,"% confidence interval for variance:","\n")
  cat("sample variance:",sampvar,"\n")
  cat("lower limit",lower,"\n")
  cat("upper limit",upper,"\n")
  cat("confidence interval for standard deviation:","\n")
  cat("sample standard deviation",sd(x),"\n")
  cat("lower limit",sqrt(lower),"\n")
  cat("upper limit",sqrt(upper),"\n")
}