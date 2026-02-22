#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>




int main(){

   int a = 5;
   int *p = &a;

   *p = 20;

   printf("Hodnota A je: %d", a);

    return 0;
}

