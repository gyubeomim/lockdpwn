quadratic <-
function(coeff) {
a <- coeff[1]
b <- coeff[2]
c <- coeff[3]
d <- b^2 - (4*a*c)
cat("The discriminant is: ",d,"\n")
if(d < 0) cat("There are no real roots. ","\n")
if(d >= 0){
root1 <- (-b + sqrt(d))/(2*a)
root2 <- (-b-sqrt(d))/(2*a)
cat("root1: ",root1,"\n")
cat("root2: ",root2,"\n")
}
}
