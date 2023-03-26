#include <gtk/gtk.h>
#include <stdbool.h>
#include "functions.h"


//globals
extern struct DiceSpot Spot[5];
int intRollsLeft;

// check for three of a kind

//          2  5  2  4  6 = 020111  false
//          5  5  5  1  2 = 110030  true
// p is an int that lets the function know what we are checking for
// 1=3 of a kind
int TheMatrix(int p)
{
   int intBoxTotal, intPips = 0;              // box total holds return score 
   int intMatrix[6] = {0};

   //set up matrix
   for (int a = 0; a < 6; a++)
   {
     for (int k = 0; k < 5; k++)
     {
         if (Spot[k].Value == a + 1)
         {
            intMatrix[a]++;
         }
      }
   }

   // 3 of a kind
   if (p == 1); 
   {
      
      intBoxTotal = 0;
      
      for (int k = 0; k < 6; k++) 
      {
         if (intMatrix[k] > 2)         // 3 of a kind sets bool w[1] to true
         {
            for (int m = 0; m < 6; m++)
            {
               intBoxTotal = intBoxTotal + Spot[m].Value;
            }
            return intBoxTotal;
         }  
      }
      intBoxTotal = 0;
      return intBoxTotal;   
   } 
   
   // 4 of a kind
   if (p == 2); 
   {
      intBoxTotal = 0;
      for (int a = 0; a < 6; a++)
      {
         if (intMatrix[a] > 3)         // 4 of a kind sets bool w[1] to true 
         {
               for (int k = 0; k < 6; k++) 
               {
                  intBoxTotal = intBoxTotal + Spot[k].Value;
               }
               return intBoxTotal;
         }
      }
      intBoxTotal = 0;
      return intBoxTotal;
   }

   
}

//Check to see if top half is done ant do top totals and bonus
bool CheckTop()
{
   bool a;
   if (intTopSpots == 6)
   {
      a = true;
   }
   else
   {
      a = false;
   }
   return a;
}

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
void ResetTurn()
{        
   for (int x = 0; x < 5; x++)
   {

      //Spot[x].FileName = "6.png";
      Spot[x].Value = rand () % 6 +1;
      Spot[x].Hold = false;
   }
   intRollsLeft = 3;
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
      Spot[i].Hold = false; 
   }
   return q;
}

//assign and calculate ace to six spots on score card
gchar *ScoreTop(int a)
{
   int intTotalPip = 0;
   for (int x = 0; x < 5; x++)
   {
      if(Spot[x].Value == a)
      {
         intTotalPip = intTotalPip + a;
      }      
   }
   intRollsLeft = 3;
   intScore[0] = intScore[0] + intTotalPip;
   //convert int to gchar
   gchar *display;
   display = g_strdup_printf("%d", intTotalPip);  
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