// servak.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define WIN32_LEAN_AND_MEAN // Отключаем редко используемые компоненты Windows

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
using namespace std;

int main()
{
    // Инициализируем библиотеку Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cout << "WSAStartup failed with error: " << result << endl;
        return 1;
    }

    // Создаем сокеты для подключения и прослушивания
    SOCKET ConnectSocket = INVALID_SOCKET;
    SOCKET ListenSocket = INVALID_SOCKET;

    // Обнуляем структуру hints и заполняем её необходимыми данными для создания сокета
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // Используем IPv4
    hints.ai_socktype = SOCK_STREAM; // Потоковый сокет
    hints.ai_protocol = IPPROTO_TCP; // Протокол TCP
    hints.ai_flags = AI_PASSIVE; // Сокет для прослушивания

    // Получаем информацию о локальном адресе и порте для создания и привязки сокета
    result = getaddrinfo(NULL, "666", &hints, &addrResult);
    if (result != 0) {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    // Создаем сокет для прослушивания входящих соединений
    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Привязываем сокет к IP-адресу и порту
    result = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR) {
        cout << "Bind failed with error: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Настраиваем сокет на прослушивание входящих соединений
    result = listen(ListenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        cout << "Listen failed with error: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Принимаем входящее соединение
    ConnectSocket = accept(ListenSocket, NULL, NULL);
    if (ConnectSocket == INVALID_SOCKET) {
        cout << "Accept failed with error: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Закрываем сокет для прослушивания, так как он больше не нужен
    closesocket(ListenSocket);

    // Цикл для получения данных от клиента
    char recvBuffer[512];
    do {
        ZeroMemory(recvBuffer, 512); // Обнуляем буфер перед приемом данных
        result = recv(ConnectSocket, recvBuffer, 512, 0); // Принимаем данные от клиента
        if (result > 0) {
            cout << "Received " << result << " bytes: " << recvBuffer << endl;
        }
        else if (result == 0) {
            cout << "Connection closing..." << endl;
        }
        else {
            cout << "Recv failed with error: " << WSAGetLastError() << endl;
            closesocket(ConnectSocket);
            freeaddrinfo(addrResult);
            WSACleanup();
            return 1;
        }
    } while (result > 0);

    // Корректное завершение соединения
    result = shutdown(ConnectSocket, SD_SEND);
    if (result == SOCKET_ERROR) {
        cout << "Shutdown failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }


    // Освобождение ресурсов и завершение работы
    closesocket(ConnectSocket);
    freeaddrinfo(addrResult);
    WSACleanup();
    return 0;
}
