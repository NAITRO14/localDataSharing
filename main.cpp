#include "header.h"



int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	Fl_Double_Window* win = new Fl_Double_Window(800, 600, "Main window");

	
	
	win->end();
	win->show(argc, argv);
	
	return 0;
}