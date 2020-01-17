## Function to estimate the required sample
## size for a desired margin of error.
## From Chapter 8 of Beginning R by Larry Pace
sampsize.est <- function(E, sigma, alpha = .05){
  # E is the desired margin of error
  n <- ((qnorm(alpha/2)*sigma)/E)^2
  estsize <- ceiling(n)
  cat("\t","sample size estimation","\n")
  cat("For a desired margin of error of:",E,"the required sample size is:",estsize,".","\n")
}
