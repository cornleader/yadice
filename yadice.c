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


struct DiceSpot Spot[4];




// set up widget pointers
GtkWidget *Fixed1, *Window1, *btnRoll; 
GtkWidget *imgA, *imgB, *imgC, *imgD, *imgE;
GtkWidget *btnA, *btnB, *btnC, *btnD, *btnE; 
GtkBuilder	*builder;


//*******************************************************
// int main. build window and elements usig glade file
//*******************************************************
 
int main(int argc, char *argv[]) 
{
    NewGame();

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
    btnRoll= GTK_WIDGET(gtk_builder_get_object(builder, "btnRoll"));
  
    gtk_widget_show(Window1);
	gtk_main();
        

	return EXIT_SUCCESS;
}
//*************************************************************************
//                       window generation complete
//*************************************************************************



int on_btnRoll_clicked (GtkButton *b)
{
    for (int i = 0; i < 5; i++)
    {
        Spot[i].Value = rand () % 6 +1;
        Spot[i].FileName = SelectImage(Spot[i].Value);
    }

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
