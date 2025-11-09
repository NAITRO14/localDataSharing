#pragma once
#define NOMINMAX
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <WS2tcpip.h>
#include <conio.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

template <typename T>
inline void enter_num(T& num)
{
	cout << "¬вод: ";
	while (true) {
		if (cin >> num) {  // если ввод корректный
			break;         // выйти из цикла
		}
		else {
			cout << "ќшибка ввода. ¬ведите число заново." << endl;
			cout << "¬вод: ";
			cin.clear(); // очистка ошибки
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистить буфер
		}
	}
}

bool iAmHost();
bool iAmClient();

int ent_port();

