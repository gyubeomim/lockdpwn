  #include <stdio.h>

  void swap(int *, int *);

  int
  main(void)
  {
    int i = 0;
    int j = 1;

    printf("i = %d, j = %d\n", i, j);
    swap(&i, &j);

    printf("i = %d, j = %d\n", i, j);
    return 0;
  }

  static void
  do_swap(int *lhs, int *rhs, int *tmp)
  {
    *tmp = *lhs;
    *lhs = *rhs;
    *rhs = *tmp;
  }

  void
  swap(int *lhs, int *rhs)
  {
    int t;
    do_swap(lhs, rhs, &t);
  }
