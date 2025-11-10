#pragma once
#define NOMINMAX
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <WS2tcpip.h>
#include <conio.h>
#include <string>

//графика
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>

//потоки
#include <thread>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct menues
{
	Fl_Group* roleGr;
	Fl_Group* hostGr;
	Fl_Group* clientGr;
};
extern menues menu;

struct AppData
{
	int* port;
	string* ipAddr;
	Fl_Input* inp;
};
extern AppData Data;

template <typename T>
inline void enter_num(T& num)
{
	cout << "Ввод: ";
	while (true) {
		if (cin >> num) {  // если ввод корректный
			break;         // выйти из цикла
		}
		else {
			cout << "Ошибка ввода. Введите число заново." << endl;
			cout << "Ввод: ";
			cin.clear(); // очистка ошибки
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистить буфер
		}
	}
}

bool iAmHost(int port);
bool iAmClient();

//---------------
void hstBtPrsd(Fl_Widget* w, void* data);
void open_serverBtn(Fl_Widget* w, void* data);

void client_connected(void* data);

int enter_port(Fl_Widget* w, void* data);

