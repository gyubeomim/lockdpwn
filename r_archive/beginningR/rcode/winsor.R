##############################################################################
## Function to calculate Winsorized variance                                ##
## adapted from a function posted by Jim Lemon.                             ##  
## Define the desired quantiles and substitue the quantiles for extreme     ##
## values of x.                                                             ##
##############################################################################
winsor.var <- function(x, probs = c(0.20, 0.80)) {
	quant <- quantile(x, probs = probs)
	x[x < quant[1]] <- quant[1] # substitute the value at the quantile for x
	x[x > quant[2]] <- quant[2] # substitute the value at the quantile for x
	return(var(x))
	}
