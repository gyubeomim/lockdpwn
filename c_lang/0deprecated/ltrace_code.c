/*
  c ==> CTF, ltrace
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char buf[32];
  char key[] = "d3m0_pr0gr4m_k3y";

  puts("Please input the passphase");
  fgets(buf, sizeof(buf), stdin);
  strtok(buf, "\n");

  if (!strcmp(buf, key))
  {
    puts("Congratulations! Your flag is ctf4b{7h15_15_51pl3_ltrace}");
  }
  else
  {
    puts("Invalid inputs");
  }

  return 0;
}
