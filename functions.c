#include <gtk/gtk.h>
#include <stdbool.h>
#include "functions.h"

extern struct DiceSpot Spot[4];


char *SelectImage(int a)
{
    char *image;

    switch(a) 
    {
      case 1 :
         image = "1.png";
         break;
      case 2 :
        image = "2.png";
        break;
      case 3 :
         image = "3.png";
         break;
      case 4 :
         image = "4.png";
         break;
      case 5 :
         image = "5.png";
         break;
      case 6 :
        image = "6.png";
        break;
   }
   return image;
}


void NewGame()
{        
    srand(time(NULL));
    for (int x = 0; x < 5; x++)
    {

        Spot[x].FileName = "6.png";
        Spot[x].Value = rand () % 6 +1;
        Spot[x].Hold = false;
    }
}


//equivlent of strcat() but using pointers
char* CombineStrings(int *A, const char*B)
{           
    //int lenA = strlen(A);
    int lenA = 1;
    int lenB = strlen(B);
    char *C = (char*) malloc(lenA + lenB + 1);
    memcpy(C, A, lenA);
    memcpy(C + lenA, B, lenB);
    C[lenA + lenB] = '\0';    
    return C;
}