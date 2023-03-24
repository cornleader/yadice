#include <gtk/gtk.h>
#include <stdbool.h>
#include "functions.h"


//global struct
extern struct DiceSpot Spot[4];

//selects the proper image for each dice spot
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

//clear structure
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

//hold specific dice spots and change button display
char *Hold(int i)
{
   char *q;
   if (Spot[i].Hold == false)
   {
      q = "HOLD";
      Spot[i].Hold = true;
    
   }
   else
   {
      q = "Roll";
      Spot[0].Hold = false; 
   }
   return q;
}

//assign and calculate ace to six spots on score card
gchar *ScoreTop(int a)
{
   int intTotal = 0;
   for (int x = 0; x < 5; x++)
   {
      if(Spot[x].Value == a)
      {
         intTotal = intTotal + a;
      }      
   }
   //convert int to gchar
   gchar *display;
   display = g_strdup_printf("%d", intTotal);  
   //********************
   return display;
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