/*
  c++ ==> emacs lisp 사용법 강좌에 나온 ceaser 암호화를 하는 간단한 예제 코드

  code from http://tsgates.github.io/emacsbook/chap8.html
*/
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

#define PRIME (17)
#define SHIFT (11)

/**
 * @plain: input text
 * @shift: an integer
 * @prime: a prime number
 */
char* ceaser(const char *plain, int shift, int prime) {
    const int len =strlen(plain);
    char *cipher = (char *)malloc(len);

    for (int i=0; i<len; i++) {
        *(cipher + i) = (*(plain + i) - 'a' + shift) % prime + 'a';
    }

    *(cipher + len) = '\0';
    return cipher;
}

int main(int argc, char **argv){
    if(argc != 2){
        err(1, "usage: %s [text]\n", argv[0]);
    }

    const char *encrypted = ceaser(argv[1], SHIFT, PRIME);
    const char *decrypted = ceaser(encrypted, -SHIFT, PRIME);

    printf("'%s' =enc->> '%s' =dec->> '%s'\n", argv[1], encrypted, decrypted);

    return 0;
}
