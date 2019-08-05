'''
	R ==> 유전자알고리즘을 사용해 
			y = 3x^2 - 2x + 5 (-20 < x < 20)
			y = (x1-2)^2 + (x2-5)^2 + 10의 최소값을 찾아내는 코드

'''
library(GA)
f <- function(x) 3*x*x - 2 *x + 5
# fitness는 ga의 목표값이다
# 가장 최대의 값으로 가려는 성향이 있으므로 -f(x)를 넣어줘 가장 최소의 값을 찾는 방향으로 수정한다
fitness <- function(x) - f(x)

# 최대 20, 최소 -20으로 설정하고 개체수는 50, 최대 100 세대의 반복을 실행한다
GA <- ga(type = "real-valued", fitness = fitness, min = -20, max = 20, popSize = 50, maxiter= 100)

summary(GA)
plot(GA)
curve(f, -5, 5)
abline(v= GA@solution, lty = 3)




# 2개의 인자를 가진 함수의 최소값을 찾는다
test1 <- function(x1,x2) (x1-2)^2 + (x2-5)^2 + 10
x1 <- seq(-10, 10, by = 0.1)
x2 <- seq(-10, 10, by = 0.1)
f <- outer(x1,x2, test1)

# 3d 도면을 그려본다
persp3D(x1, x2, f, theta = 30, phi = 30)
filled.contour(x1,x2,f,color.palette = jet.colors)

# 최소(-10,-10) 부터 최대(10,10) 까지 탐색하고 초기 개체수는 30개, 최대 100세대 까지 반복한다
GA <- ga(type = "real-valued", fitness = function(x) -test1(x[1],x[2]), min =c(-10,-10), max = c(10,10), popSize = 30, maxiter= 100)
summary(GA)

plot(GA)









# 출처 : https://books.google.co.kr/books?id=2XMRAgAAQBAJ&pg=PT10&lpg=PT10&dq=r+%EC%9C%A0%EC%A0%84%EC%9E%90%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98&source=bl&ots=QWFmva3T1p&sig=sRfMP0hCMPlYn3_x47SiOjoQdJU&hl=ko&sa=X&ved=0ahUKEwjAityS1ozTAhXLilQKHWEIDccQ6AEISzAF#v=onepage&q=%EC%9C%A0%EC%A0%84%EC%9E%90&f=false










