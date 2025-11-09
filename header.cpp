#include "header.h"



bool iAmHost()
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
	serverAddr.sin_port = htons(54000);

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

	//Получение данных от клиента
	char buf[1024];
	while (true)
	{
		ZeroMemory(buf, sizeof(buf));

		int bytesRecived = recv(clientSocket, buf, sizeof(buf), 0);
		if (bytesRecived > 0)
		{
			cout << "Получено сообщение от клиента: " << string(buf, 0, bytesRecived) << endl;
		}

	}
	closesocket(clientSocket);
	closesocket(listenSocket);
	WSACleanup();
}

bool iAmClient()
{
	// 1. Инициализация Winsock
	WSADATA wsaData;
	int wsOk = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsOk != 0) {
		std::cerr << "Ошибка инициализации Winsock! Код: " << wsOk << "\n";
		return 1;
	}

	// 2. Создание TCP сокета
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Ошибка создания сокета!\n";
		WSACleanup();
		return 1;
	}

	// 3. Указание IP и порта сервера
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	// ВАЖНО: здесь задаем IP сервера (например, "192.168.1.5" или "127.0.0.1" для localhost)
	inet_pton(AF_INET, "10.109.171.66", &serverAddr.sin_addr); // Замените на нужный IP!
	serverAddr.sin_port = htons(54000); // Порт, на котором слушает сервер

	// 4. Попытка подключения к серверу
	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		std::cerr << "Ошибка подключения к серверу!\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	std::cout << "Подключение к серверу установлено!\n";

	string massage;
	while (true)
	{
		// 5. Отправка сообщения серверу
		cout << "Вводите строку для отправки: ";
		getline(cin, massage);
		if (massage == "0")
		{
			break;
		}
		int bytesSent = send(sock, massage.c_str(), strlen(massage.c_str()), 0);
		if (bytesSent == SOCKET_ERROR) {
			std::cerr << "Ошибка отправки данных!\n";
		}
	}
	

	// 6. Закрытие сокета и очистка Winsock
	closesocket(sock);
	WSACleanup();
	return 0;
}
