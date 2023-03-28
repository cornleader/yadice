#include <gtk/gtk.h>
#include <stdbool.h>
#include <gtk/gtkx.h>

struct DiceSpot
{
    char *FileName;
    int Value;
    bool Hold;
};

extern int intRollsLeft;        //keep track of remaining rolls per turn
extern int intTopSpots;         //keeps track of when all top slots have been filled
extern int intBotSpots;         //keeps track of when all top bottom have been filled
extern int intScore[2];

//declare functions
char *CombineStrings(int *A, const char*B);
char *SelectImage(int a);
void ResetTurn();
char *Hold(int i);
gchar *ScoreTop(int a);
//bool CheckTop();
//void Display();
bool CheckLR(int v);
int TheMatrix(int p);
