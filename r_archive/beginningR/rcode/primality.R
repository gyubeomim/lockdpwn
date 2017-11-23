primality <-
function(x) {
stopifnot(x >= 2)
limit <- trunc(sqrt(x) + 1)
testvec <- 2:limit
results <- x %% testvec
check <- any(results == 0)
outcome <- "Yes."
if(check == TRUE) outcome <- "No."
if(x == 2) outcome <- "Yes."
cat("Is",x,"prime?",outcome,"\n")
}
