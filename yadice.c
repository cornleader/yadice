/****************************************************************
*                                                               *
*                           Yadice                              *
*                                                               *
*****************************************************************
*                                                               *
*        filename: yadice.c               date: 20/3/2023       *
*    dependencies: GTK              programmer: Tim             *
*      glade file: yadice             platform: linux           *
*                                                               *
*****************************************************************
*                          OBJECTIVE                            *
*                                                               *
*   Remake of the classic dice game Yatzee.                     *
*                                                               *
****************************************************************/

//  includes
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include "functions.h"
#include <stdbool.h>

//Create a global struct to manage each of the 5 dice images and their parameters.
struct DiceSpot Spot[5];
int intTopSpots = 0;
int intScore[2];



// set up widget pointers
GtkWidget *Fixed1, *Window1, *btnRoll; 
GtkWidget *imgA, *imgB, *imgC, *imgD, *imgE;
GtkWidget *btnA, *btnB, *btnC, *btnD, *btnE; 
GtkWidget *chk1, *chk2, *chk3, *chk4, *chk5, *chk6; 
GtkWidget *lbl1, *lbl2, *lbl3, *lbl4, *lbl5, *lbl6;
GtkWidget *lblTopTotal1, *lblTopTotal2, *lblBonus;
GtkBuilder	*builder;

void ResetHold();
void *DisplayDice();
void FinishTop();
//*******************************************************
// int main. build window and elements usig glade file
//*******************************************************
 
int main(int argc, char *argv[]) 
{
    
    ResetTurn();
    srand(time(NULL));
    intScore[0] = 0;
    intScore[1] = 0;
    
	gtk_init(&argc, &argv); // init Gtk

    // connect to xml file, yadice.glade, to build window on screen 
	builder = gtk_builder_new_from_file ("yadice.glade");
    Window1 = GTK_WIDGET(gtk_builder_get_object(builder, "Window1"));
	g_signal_connect(Window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

	//build screen objects  
    Fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"Fixed1"));
	btnA = GTK_WIDGET(gtk_builder_get_object(builder, "btnA"));
	btnB = GTK_WIDGET(gtk_builder_get_object(builder, "btnB"));
   	btnC = GTK_WIDGET(gtk_builder_get_object(builder, "btnC"));
	btnD = GTK_WIDGET(gtk_builder_get_object(builder, "btnD"));
    btnE = GTK_WIDGET(gtk_builder_get_object(builder, "btnE"));
    imgA = GTK_WIDGET(gtk_builder_get_object(builder, "imgA"));
    imgB = GTK_WIDGET(gtk_builder_get_object(builder, "imgB"));
    imgC = GTK_WIDGET(gtk_builder_get_object(builder, "imgC"));
    imgD = GTK_WIDGET(gtk_builder_get_object(builder, "imgD"));
    imgE = GTK_WIDGET(gtk_builder_get_object(builder, "imgE"));
    chk1 = GTK_WIDGET(gtk_builder_get_object(builder, "chk1"));
    chk2 = GTK_WIDGET(gtk_builder_get_object(builder, "chk2"));
    chk3 = GTK_WIDGET(gtk_builder_get_object(builder, "chk3"));
    chk4 = GTK_WIDGET(gtk_builder_get_object(builder, "chk4"));
    chk5 = GTK_WIDGET(gtk_builder_get_object(builder, "chk5"));
    chk6 = GTK_WIDGET(gtk_builder_get_object(builder, "chk6"));
    lbl1 = GTK_WIDGET(gtk_builder_get_object(builder, "lbl1"));
    lbl2 = GTK_WIDGET(gtk_builder_get_object(builder, "lbl2"));
    lbl3 = GTK_WIDGET(gtk_builder_get_object(builder, "lbl3"));
    lbl4 = GTK_WIDGET(gtk_builder_get_object(builder, "lbl4"));
    lbl5 = GTK_WIDGET(gtk_builder_get_object(builder, "lbl5"));
    lbl6 = GTK_WIDGET(gtk_builder_get_object(builder, "lbl6"));
    btnRoll= GTK_WIDGET(gtk_builder_get_object(builder, "btnRoll"));
    lblTopTotal1 = GTK_WIDGET(gtk_builder_get_object(builder, "lblTopTotal1"));
    lblTopTotal2 = GTK_WIDGET(gtk_builder_get_object(builder, "lblTopTotal2"));
    lblBonus = GTK_WIDGET(gtk_builder_get_object(builder, "lblBonus"));
   
    gtk_widget_show(Window1);

  
  
    gtk_main();
  
  
	return EXIT_SUCCESS;
}
//*************************************************************************
//                       window generation complete
//*************************************************************************



int on_btnRoll_clicked (GtkButton *b)
{
    if (intRollsLeft > 0)
    { 
        for (int i = 0; i < 5; i++)
        {
            if (Spot[i].Hold == false)
            {
                Spot[i].Value = rand () % 6 +1;
                Spot[i].FileName = SelectImage(Spot[i].Value);
            }
        }
        intRollsLeft--;
    }
    DisplayDice();
}

// hold buttons
int on_btnA_clicked (GtkButton *b)
{
    if (intRollsLeft == 3)
    {
        return 0;
    }
    char *s;
    s = Hold(0);
    gtk_button_set_label(GTK_BUTTON(btnA), s);
    
}
int on_btnB_clicked (GtkButton *b)
{
    if (intRollsLeft == 3)
    {
        return 0;
    }
    char *s;
    s = Hold(1);
    gtk_button_set_label(GTK_BUTTON(btnB), s);
}
int on_btnC_clicked (GtkButton *b)
{
    if (intRollsLeft == 3)
    {
        return 0;
    }
    char *s;
    s = Hold(2);
    gtk_button_set_label(GTK_BUTTON(btnC), s);
}
int on_btnD_clicked (GtkButton *b)
{
    if (intRollsLeft == 3)
    {
        return 0;
    }
    char *s;
    s = Hold(3);
    gtk_button_set_label(GTK_BUTTON(btnD), s);
}
int on_btnE_clicked (GtkButton *b)
{
    if (intRollsLeft == 3)
    {
        return 0;
    }
    char *s;
    s = Hold(4);
    gtk_button_set_label(GTK_BUTTON(btnE), s);
}

//checkmark buttons for 1 to 6
int on_chk1_toggled(GtkToggleButton *t)
{   
    if (intRollsLeft == 3)
    {
        return 0;
    }
    intTopSpots++;
    gtk_widget_hide(GTK_WIDGET(chk1));
    gchar *TotalScore;
    TotalScore = ScoreTop(1);
    gtk_label_set_text (GTK_LABEL(lbl1), (const gchar* )TotalScore);
    ResetTurn();
    ResetHold();
    
    gchar *display;
    display = g_strdup_printf("%d", intScore[0]);
    gtk_label_set_text (GTK_LABEL(lblTopTotal1), (const gchar* )display);
    bool a = CheckTop();
    if (a == true)
    {
        FinishTop();
    }
}
int on_chk2_toggled(GtkToggleButton *t)
{   
    if (intRollsLeft == 3)
    {
        return 0;
    }
    intTopSpots++;
    gtk_widget_hide(GTK_WIDGET(chk2));
    gchar *TotalScore;
    TotalScore = ScoreTop(2);
    gtk_label_set_text (GTK_LABEL(lbl2), (const gchar* )TotalScore);
    ResetTurn();
    ResetHold();
    
    gchar *display;
    display = g_strdup_printf("%d", intScore[0]);
    gtk_label_set_text (GTK_LABEL(lblTopTotal1), (const gchar* )display);
    bool a = CheckTop();
    if (a == true)
    {
        FinishTop();
    }
}
int on_chk3_toggled(GtkToggleButton *t)
{   
    if (intRollsLeft == 3)
    {
        return 0;
    }
    intTopSpots++;
    gtk_widget_hide(GTK_WIDGET(chk3));
    gchar *TotalScore;
    TotalScore = ScoreTop(3);
    gtk_label_set_text (GTK_LABEL(lbl3), (const gchar* )TotalScore);
    ResetTurn();
    ResetHold();
    
    gchar *display;
    display = g_strdup_printf("%d", intScore[0]);
    gtk_label_set_text (GTK_LABEL(lblTopTotal1), (const gchar* )display);
    bool a = CheckTop();
    if (a == true)
    {
        FinishTop();
    }
}
int on_chk4_toggled(GtkToggleButton *t)
{   
    if (intRollsLeft == 3)
    {
        return 0;
    }
    intTopSpots++;
    gtk_widget_hide(GTK_WIDGET(chk4));
    gchar *TotalScore;
    TotalScore = ScoreTop(4);
    gtk_label_set_text (GTK_LABEL(lbl4), (const gchar* )TotalScore);
    ResetTurn();
    ResetHold();
    
    gchar *display;
    display = g_strdup_printf("%d", intScore[0]);
    gtk_label_set_text (GTK_LABEL(lblTopTotal1), (const gchar* )display);
    bool a = CheckTop();
    if (a == true)
    {
        FinishTop();
    }
}
int on_chk5_toggled(GtkToggleButton *t)
{   
    if (intRollsLeft == 3)
    {
        return 0;
    }
    intTopSpots++;
    gtk_widget_hide(GTK_WIDGET(chk5));
    gchar *TotalScore;
    TotalScore = ScoreTop(5);
    gtk_label_set_text (GTK_LABEL(lbl5), (const gchar* )TotalScore);
    ResetTurn();
    ResetHold();
    
    gchar *display;
    display = g_strdup_printf("%d", intScore[0]);
    gtk_label_set_text (GTK_LABEL(lblTopTotal1), (const gchar* )display);
    bool a = CheckTop();
    if (a == true)
    {
        FinishTop();
    }
}
int on_chk6_toggled(GtkToggleButton *t)
{   
    if (intRollsLeft == 3)
    {
        return 0;
    }
    intTopSpots++;
    gtk_widget_hide(GTK_WIDGET(chk6));
    gchar *TotalScore;
    TotalScore = ScoreTop(6);
    gtk_label_set_text (GTK_LABEL(lbl6), (const gchar* )TotalScore);
    ResetTurn();
    ResetHold();
    
    gchar *display;
    display = g_strdup_printf("%d", intScore[0]);
    gtk_label_set_text (GTK_LABEL(lblTopTotal1), (const gchar* )display);
    bool a = CheckTop();
    if (a == true)
    {
        FinishTop();
    }
}

void ResetHold()
{
    const gchar *z = "Roll";
    gtk_button_set_label(GTK_BUTTON(btnA), z);
    gtk_button_set_label(GTK_BUTTON(btnB), z);
    gtk_button_set_label(GTK_BUTTON(btnC), z);
    gtk_button_set_label(GTK_BUTTON(btnD), z);
    gtk_button_set_label(GTK_BUTTON(btnE), z);
}

void *DisplayDice()
{
    const gchar *charA = Spot[0].FileName;
    const gchar *charB = Spot[1].FileName;
    const gchar *charC = Spot[2].FileName;
    const gchar *charD = Spot[3].FileName;
    const gchar *charE = Spot[4].FileName;
    gtk_image_set_from_file (GTK_IMAGE(imgA), (const gchar* )charA);
    gtk_image_set_from_file (GTK_IMAGE(imgB), (const gchar* )charB);
    gtk_image_set_from_file (GTK_IMAGE(imgC), (const gchar* )charC);
    gtk_image_set_from_file (GTK_IMAGE(imgD), (const gchar* )charD);
    gtk_image_set_from_file (GTK_IMAGE(imgE), (const gchar* )charE);
}

void FinishTop()
{
    gchar *z;
    //intScore[0] = 63;       //test data to ensure bonus is working
    if(intScore[0] > 62)
    {
        intScore[0] = intScore[0] + 35;
        z = "35";
        gtk_label_set_text (GTK_LABEL(lblBonus), (const gchar* )z);

    }
    else
    {
        z = "0";
        gtk_label_set_text (GTK_LABEL(lblBonus), (const gchar* )z);
    }
    gchar *display;
    display = g_strdup_printf("%d", intScore[0]);
    gtk_label_set_text (GTK_LABEL(lblTopTotal2), (const gchar* )display);
}