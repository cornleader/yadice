#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <stdbool.h>
#include "functions.h"
#include <stdbool.h>


//globals
extern struct DiceSpot Spot[5];
int intRollsLeft;


/****************************************************************
*                   T H E   M A T R I X                         *
*****************************************************************
*                  2  5  2  4  6 = 020111                       *
*                  5  5  5  1  2 = 110030                       *
*                                                               *
*  p is an int that lets the function know what we are checking *
*  for.                                                         *
*  1 - 3 of a kind                                              *
*  2 - 4 of a kind                                              *
*  4 - full house                                               *
*****************************************************************/
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
   if (p == 1) 
   {
      
      intBoxTotal = 0;
      
      for (int i = 0; i < 6; i++) 
      {
         if (intMatrix[i] > 2)         // 3 of a kind sets bool w[1] to true
         {
            for (int x = 0; x < 5; x++)
            {
               intBoxTotal = intBoxTotal + Spot[x].Value;
            }
            return intBoxTotal;
         }  
      }
      intBoxTotal = 0;
      return intBoxTotal;   
   } 
   
   // 4 of a kind
   else if (p == 2) 
   {
      intBoxTotal = 0;
      for (int k = 0; k < 6; k++)
      {
         if (intMatrix[k] > 3)         // 4 of a kind totals dice 
         {
               for (int m = 0; m < 5; m++) 
               {
                  intBoxTotal = intBoxTotal + Spot[m].Value;
               }
               return intBoxTotal;
         }
      }
      intBoxTotal = 0;
      return intBoxTotal;
   }

   // full house
   else if (p == 3)
   {
      bool i[2] = {false};                   // one for a 2 and one for a 3 in matrix
      int r = 0;
      for (int x = 0; x < 5; x++)
      {
         if(intMatrix[x] == 2)
         {
            i[0] = true;
         }
         if(intMatrix[x] == 3)
         {
            i[1] = true;
         }
      }
      if (i[0] == true && i[1] == true)
      {
         r = 25;
         return r;                           
      }
      else
      {
         r = 0;
         return r;
      }
   }
   //sm straight
   // 1 1 1 1 0 0
   // 0 1 1 1 1 0
   // 0 0 1 1 1 1
   else if (p == 4)
   {
      if(intMatrix[0] > 0 && intMatrix[1] > 0 && intMatrix[2] > 0 && intMatrix[3] > 0)
      {
         int r = 30;
         return r;
      }
      if(intMatrix[4] > 0 && intMatrix[1] > 0 && intMatrix[2] > 0 && intMatrix[3] > 0)
      {
         int r = 30;
         return r;
      }
      if(intMatrix[4] > 0 && intMatrix[5] > 0 && intMatrix[2] > 0 && intMatrix[3] > 0)
      {
         int r = 30;
         return r;
      }
   }
   //lg straight
   // 1 1 1 1 1 0
   // 0 1 1 1 1 1
   else if (p == 5)
   {
      if(intMatrix[0] > 0 && intMatrix[1] > 0 && intMatrix[2] > 0 && intMatrix[3] > 0 && intMatrix[4] > 0)
      {
         int r = 40;
         return r;
      }
      if(intMatrix[4] > 0 && intMatrix[5] > 0 && intMatrix[2] > 0 && intMatrix[3] > 0 && intMatrix[1] > 0)
      {
         int r = 40;
         return r;
      }
   }
   // yathzee 
   else if (p == 6) 
   {
      for (int k = 0; k < 6; k++)
      {
         if (intMatrix[k] == 5)         // 4 of a kind totals dice 
         {
               int r = 50;
               return r;
         }
      }
      int r = 0;
      return r;
   }
   else if (p == 7) 
   {  
      int r = 0;
      for (int x = 0; x < 5; x++)
      {
         r = r + Spot[x].Value;
      }
      return r;
   } 
}

// Check to see if left or right is done ant do totals and bonus
// v parameter recieves a 1 for left or 2 for right
// bool a is true when all spots have been filled for left or right
bool CheckLR(int v)
{
   bool a;
   if(v == 1)
   {
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
   if(v == 2)
   {
      if (intBotSpots == 7)
      {
         a = true;
      }
      else
      {
         a = false;
      }
      return a;
   }
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