// Clientic.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define WIN32_LEAN_AND_MEAN // Отключаем редко используемые компоненты Windows

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
using namespace std;

int main()
{
    // Структура WSADATA используется для хранения информации о версии и реализации Windows Sockets
    WSADATA wsaData;
    // Создаем сокет для подключения
    SOCKET ConnectSocket = INVALID_SOCKET;

    ADDRINFO hints; // Структура для хранения информации о сокете
    ADDRINFO* addrResult = nullptr; // Указатель для хранения результатов функции getaddrinfo
    const char* sendBuffer1 = "The whole world is a database, and you are just a sign in it";
    const char* sendBuffer2 = "pretium pecuniae sciens, de valore vitae noli oblivisci";
    char recvBuffer[512]; // Буфер для хранения полученных данных

    // Инициализация библиотеки Winsock, определение версии 2.2
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cout << "WSAStartup failed with error: " << result << endl;
        return 1;
    }

    // Обнуляем структуру hints и заполняем её необходимыми данными для создания сокета
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // Используем IPv4
    hints.ai_socktype = SOCK_STREAM; // Потоковый сокет
    hints.ai_protocol = IPPROTO_TCP; // Протокол TCP

    // Получаем информацию о сервере
    result = getaddrinfo("localhost", "666", &hints, &addrResult);
    if (result != 0) {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    // Создаем сокет для подключения к серверу
    ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Подключаемся к серверу
    result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR) {
        cout << "Connection failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Отправляем первое сообщение серверу
    result = send(ConnectSocket, sendBuffer1, (int)strlen(sendBuffer1), 0);
    if (result == SOCKET_ERROR) {
        cout << "Send failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }
    cout << "Sent " << result << " bytes: " << sendBuffer1 << endl;

    // Отправляем второе сообщение серверу
    result = send(ConnectSocket, sendBuffer2, (int)strlen(sendBuffer2), 0);
    if (result == SOCKET_ERROR) {
        cout << "Send failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }
    cout << "Sent " << result << " bytes: " << sendBuffer2 << endl;

    // Завершаем отправку данных
    result = shutdown(ConnectSocket, SD_SEND);
    if (result == SOCKET_ERROR) {
        cout << "Shutdown failed with error: " << WSAGetLastError() << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    // Прием данных от сервера
    do {
        ZeroMemory(recvBuffer, 512); // Обнуляем буфер перед приемом данных
        result = recv(ConnectSocket, recvBuffer, 512, 0); // Принимаем данные от сервера
        if (result > 0) {
            cout << "Received " << result << " bytes: " << recvBuffer << endl;
        }
        else if (result == 0) {
            cout << "Connection closed" << endl;
        }
        else {
            cout << "Recv failed with error: " << WSAGetLastError() << endl;
        }
    } while (result > 0);

    // Освобождение ресурсов и завершение работы
    closesocket(ConnectSocket);
    freeaddrinfo(addrResult);
    WSACleanup();
    return 0;
}
