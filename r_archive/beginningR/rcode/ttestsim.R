mu <- 500
sigma <- 100
n <- 100
nreps <- 1000
pv <- rep(NA, nreps)
inout <- rep(NA, nreps)
for(i in 1:nreps){
	print(i)
	set.seed(i)
	x <- rnorm(n, mu, sigma)
	pv[i] <- t.test(x, mu = 500)$p.value
	lower <- t.test(x, mu = 500)$conf.int[1]
	upper <- t.test(x, mu = 500)$conf.int[2]
	inout[i] <- ifelse(500 >= lower & 500 <= upper,1,0)
	}
