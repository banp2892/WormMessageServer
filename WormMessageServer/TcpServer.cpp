#include "TcpServer.h"
#include <iostream>

TcpServer::TcpServer(int port)
    : serverPort(port), listenSock(INVALID_SOCKET), clientSock(INVALID_SOCKET), running(false) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("Ошибка инициализации Winsock");
    }
}

TcpServer::~TcpServer() {
    stop();
    WSACleanup();
}

bool TcpServer::start() {
    listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        std::cerr << "Ошибка создания сокета\n";
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Ошибка привязки порта\n";
        closesocket(listenSock);
        return false;
    }

    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Ошибка при прослушивании\n";
        closesocket(listenSock);
        return false;
    }

    std::cout << "Ожидание подключения клиента...\n";
    clientSock = accept(listenSock, nullptr, nullptr);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "Ошибка принятия подключения\n";
        closesocket(listenSock);
        return false;
    }

    running = true;
    std::cout << "Клиент подключен!\n";
    return true;
}

std::string TcpServer::receiveData() {
    if (!running) return "";

    char buffer[512];
    int bytesReceived = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        return std::string(buffer);
    }
    return "";
}

void TcpServer::stop() {
    if (clientSock != INVALID_SOCKET) {
        closesocket(clientSock);
        clientSock = INVALID_SOCKET;
    }
    if (listenSock != INVALID_SOCKET) {
        closesocket(listenSock);
        listenSock = INVALID_SOCKET;
    }
    running = false;
}
