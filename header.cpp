#include "header.h"

bool iAmHost(int port)
{
	//инициализация
	WSADATA wsaData;
	int wsOk = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsOk != 0)
	{
		cerr << "Ошибка иницилизации! Код: " << wsOk << endl;
		return 1;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		cerr << "Ошибка создания сокета!" << endl;
		WSACleanup();
		return 1;
	}


	//настройка адреса
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	//привязка сокета к адресу и порту
	if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cerr << "Ошибка привязки сокета!" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//переход сокета в режим прослушивания
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		cerr << "Ошибка запуска прослушивания!" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	cout << "Сервер работает на порту: " << port << endl;
	//ожидание подключение клиента
	cout << "Ожидание подключения клиента . . ." << endl;
	SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "Ошибка при принятии подключения!" << endl;
		WSACleanup();
		return 1;
	}
	cout << "Клиент подключился !" << endl;

	Fl::awake(client_connected, nullptr);

	//Получение данных от клиента
	/*char buf[1024]; char sendbuf[1024] = "Ok!";
	while (true)
	{
		ZeroMemory(buf, sizeof(buf)); 

		int bytesRecived = recv(clientSocket, buf, sizeof(buf), 0);
		if (bytesRecived > 0)
		{
			cout << "Получено сообщение от клиента: " << string(buf, 0, bytesRecived) << endl;
		}

		int bytesSent = send(clientSocket, sendbuf, sizeof(sendbuf), 0);
		if (bytesSent == SOCKET_ERROR)
		{
			if (bytesSent == SOCKET_ERROR) {
				cerr << "Клиент разовал соеденение . . ." << endl;
				system("pause");
				break;
			}
		}

	}*/
	/*closesocket(clientSocket);
	closesocket(listenSocket);
	WSACleanup();*/
	return 0;
}

bool iAmClient(int port)
{
	// 1. Инициализация Winsock
	WSADATA wsaData;
	int wsOk = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsOk != 0) {
		cerr << "Ошибка инициализации Winsock! Код: " << wsOk << "\n";
		return 1;
	}

	// 2. Создание TCP сокета
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cerr << "Ошибка создания сокета!\n";
		WSACleanup();
		return 1;
	}
	Data.to_serv_soket = &sock;

	// 3. Указание IP и порта сервера
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	
	inet_pton(AF_INET, "10.109.171.66", &serverAddr.sin_addr); 
	serverAddr.sin_port = htons(1);

	// 4. Попытка подключения к серверу
	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		cerr << "Ошибка подключения к серверу!" << endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	cout << "Подключение к серверу установлено!" << endl;

	Fl::awake(server_connected, nullptr);

	return 0;
}

void hstBtPrsd(Fl_Widget* w, void* data)
{
	menu.roleGr->hide();
	menu.hostGr->show();

	Data.inp->show();
}

void open_serverBtn(Fl_Widget* w, void* data)
{
	int port = enter_port(w, data);

	Data.inp->hide();
	w->hide();
	w->parent()->child(1)->show();


	thread hostThread([port]()
		{
			bool res = iAmHost(port);
		});
	hostThread.detach();
}

void client_connected(void* data)
{
	menu.hostGr->child(1)->hide();
	menu.MainApp->show();

	thread isClientHere([]()
		{
			bool res = isClintHereChek();
		});
	isClientHere.detach();
}

int enter_port(Fl_Widget* w, void* data)
{
	Fl_Input* inp = (Fl_Input*)data;
	int port = stoi(inp->value());

	return port;
}

void clntBtPsd(Fl_Widget* w, void* data)
{
	menu.roleGr->hide();
	menu.clientGr->show();

	Data.inp->show();
}

void connect_to_server(Fl_Widget* w, void* data)
{
	int port = enter_port(w, data);

	Data.inp->hide();
	w->hide();
	w->parent()->child(1)->show();


	thread clientThread([port]()
		{
			bool res = iAmClient(port);
			if (res == 1)
			{
				Fl::awake(server_connection_failed, nullptr);
			}
		});
	clientThread.detach();

}

void server_connected(void* data)
{
	menu.clientGr->child(1)->hide();
	menu.MainApp->show();

	thread isServerHere([]()
		{
			bool res = isServerHereCheck();
			if (res == 0)
			{
				Fl::awake(disconnected, nullptr);
			}
		});
	isServerHere.detach();
}

void server_connection_failed(void* data)
{
	menu.clientGr->child(1)->hide();
	menu.errorScreen->show();
}

bool isServerHereCheck() 
{
	while (true)
	{
		const char* message = "Hello, server!";
		int messageLen = strlen(message);
		int bytesSent = send(*Data.to_serv_soket, message, messageLen, 0);
		if (bytesSent == INVALID_SOCKET)
		{
			return 0;
		}
		this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return 1;
}

bool isClintHereChek()
{
	while(true)
	{
		char buf[1024];
		ZeroMemory(buf, sizeof(buf));

		int bytesRecv = recv(*Data.to_serv_soket, buf, sizeof(buf), 0);
		if (bytesRecv == SOCKET_ERROR || bytesRecv == 0)
		{
			return 0; // ошибка или соединение закрыто
		}
		this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
	return 1;
}

void disconnected(void* data)
{
	menu.MainApp->hide();
	menu.errorScreen->show();
}


