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
void enter_num(T& num);

bool iAmHost();
bool iAmClient();

