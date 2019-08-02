MeanAbsDev <-
function(x) {
AbsDev <- abs(x - mean(x))
MAD <- mean(AbsDev)
cat("The mean absolute deviation is:", MAD, "\n")
}
