#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LEN 100
#define DIC_LEN 5

void main()
{
  char engWords[MAX_LEN][MAX_LEN] = {"sex", "orgasm", "kiss", "technic", "felachio"};
  char hanWords[MAX_LEN][MAX_LEN] = {"섹스","오르가즘","키스","테크닉","펠라치오"};

  char word[MAX_LEN] = {0};
 
  printf("한/영 사전입니다.\n");

  
  while(1)
  {
    
    printf("원하는 단어를 입력해주세요: ");
    scanf("%s",word);

    


    for(int i =0; i< DIC_LEN ; i++)
    {
      if(strcmp(word,engWords[i]) == 0)
      {
        printf("%s에 한글 번역 단어는 [%s]입니다\n",engWords[i],hanWords[i]);
        continue;
      }
      else if(strcmp(word,hanWords[i]) == 0)
      {
        printf("%s에 영어 번역 단어는 [%s]입니다\n",hanWords[i],engWords[i]);
        continue;
      }
      
    }
    

    
  }
  
  
  
}
