#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class TcpServer {
private:
    SOCKET listenSock;
    SOCKET clientSock;
    int serverPort;
    bool running;

public:
    TcpServer(int port);
    ~TcpServer();

    bool start();
    void stop();
    std::string receiveData();
};
