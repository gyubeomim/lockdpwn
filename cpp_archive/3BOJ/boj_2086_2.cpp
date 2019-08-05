/*
 * #+DESCRIPTION:  백준 2086번, 피보나치 수의 합을 푼 정답 코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         https://fatc.club/2017/03/01/534
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>

const int MOD = 1000000000;
struct Matrix {
    long long a;
    long long b;
    long long c;
    long long d;

    Matrix() {
        a=1; b=1; c=1; d=0;
    }

    Matrix(int n) {
        if(n==0) {
            a=1; b=0; c=0; d=1;
        }
    }

    Matrix mul(Matrix B){
        Matrix m;
        m.a = (a*B.a % MOD + b*B.c % MOD) % MOD;
        m.b = (a*B.b % MOD + b*B.d % MOD) % MOD;
        m.c = (c*B.a % MOD + d*B.c % MOD) % MOD;
        m.d = (c*B.b % MOD + d*B.d % MOD) % MOD;
        return m;
    }
};

Matrix idt;
Matrix sqrMat(long long n, Matrix A) {
    if(n==0) return idt;
    if(n%2)  return A.mul(sqrMat(n-1,A));

    Matrix ret = sqrMat(n/2,A);
    return ret.mul(ret);
}

long long fibSum(long long n) {
    return sqrMat(n+2, Matrix()).c - 1;
}

int main() {
    idt = Matrix(0);
    long long a,b;

    scanf("%lld%lld",&a,&b);
    printf("%lld",(fibSum(b)+MOD-fibSum(a-1))%MOD);
}
