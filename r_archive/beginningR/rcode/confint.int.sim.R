nreps <- 1000
ll <- numeric(nreps)
ul <- numeric(nreps)
n <- 100
mu <- 500
sigma <- 100
for(i in 1:nreps) {                   
  print(i)
  set.seed(i)
  x <- rnorm(n, mu, sigma)
  ll[i] <- mean(x) - qnorm(0.975)*sqrt(sigma^2/n)
  ul[i] <- mean(x) + qnorm(0.975)*sqrt(sigma^2/n)
  }