#include <gtk/gtk.h>
#include <stdbool.h>

struct DiceSpot
{
    char *FileName;
    int Value;
    bool Hold;
};

//declare functions
char *CombineStrings(int *A, const char*B);
char *SelectImage(int a);
void NewGame();

