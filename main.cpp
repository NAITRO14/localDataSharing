#include "header.h"


class tog_button : public Fl_Button
{
public:
	tog_button(int x, int y, int w, int h, const char* label = 0)
		: Fl_Button(x, y, w, h, label)
	{
		color(FL_RED);
	}

};



menues menu;
AppData Data;

int main(int argc, char** argv)
{
	SetConsoleOutputCP(CP_UTF8);

	Fl_Double_Window* win = new Fl_Double_Window(800, 600, "Main window");

		// главная группа
		Fl_Group* chooseRoleGr = new Fl_Group(0, 0, 800, 600);
		menu.roleGr = chooseRoleGr;

			Fl_Button hostB(250, 270, 100, 52.5, "Хост"); hostB.callback(hstBtPrsd, &menu);
			Fl_Button client(450, 270, 100, 52.5, "Клиент"); client.callback(clntBtPsd, &menu);

		chooseRoleGr->end();


		Fl_Input* port_inp = new Fl_Input(100, 50, 200, 40, "Введите порт");
		port_inp->hide();
		Data.inp = port_inp;


		//группа хоста
		Fl_Group* hostGr = new Fl_Group(0, 0, 800, 600);
		menu.hostGr = hostGr;

			//открыть сервер(0)
			Fl_Button open_server(350, 50, 75, 35, "Готово"); open_server.callback(open_serverBtn, port_inp);

			//ожидание клиента(1)
			Fl_Box waiting_for_client(50, 50, 200, 150, "Ожидание клиента. . .");
			waiting_for_client.box(FL_DOWN_BOX);
			waiting_for_client.color(FL_GRAY);

			waiting_for_client.hide();


			hostGr->hide();
			hostGr->end();



		//группа клиента
		Fl_Group* clientGr = new Fl_Group(0, 0, 800, 600);
			menu.clientGr = clientGr;

			//открыть сервер(0)
			Fl_Button connet_to_server(350, 50, 75, 35, "Готово"); connet_to_server.callback(connect_to_server, port_inp);

			//ожидание клиента(1)
			Fl_Box waiting_for_server(50, 50, 200, 150, "Ожидание сервера. . .");
			waiting_for_server.box(FL_DOWN_BOX);
			waiting_for_server.color(FL_GRAY);

			waiting_for_server.hide();
			

		clientGr->hide();
		clientGr->end();


		Fl_Group* MainApp = new Fl_Group(0, 0, 800, 600);
		menu.MainApp = MainApp;

			Fl_Button* b1 = new Fl_Button(50, 50, 60, 60, "Жми");
			Fl_Button* b2 = new Fl_Button(150, 50, 60, 60, "Жми");


		MainApp->hide();
		MainApp->end();

		Fl_Group* errorScreen = new Fl_Group(0, 0, 800, 600);
		menu.errorScreen = errorScreen;

			Fl_Box err(50, 50, 300, 150, "Ошибка подключения к серверу");
			err.box(FL_DOWN_BOX);
			err.color(FL_RED);


		errorScreen->hide();
		errorScreen->end();


	
	win->end();
	win->show(argc, argv);
	return Fl::run();
}