#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

/**
 * @class TcpServer
 * @brief Класс для создания простого TCP-сервера под Windows.
 * * Обеспечивает инициализацию Winsock, прослушивание порта и 
 * базовый прием данных от одного клиента.
 */
class TcpServer {
private:
    SOCKET listenSock; ///< Сокет для прослушивания входящих соединений.
    SOCKET clientSock; ///< Сокет для обмена данными с подключенным клиентом.
    int serverPort;    ///< Порт, на котором развернут сервер.
    bool running;      ///< Флаг, указывающий на активность сервера.

public:
    /**
     * @brief Конструктор сервера.
     * @param port Порт для прослушивания (например, 8080).
     * @note Инициализирует библиотеку Winsock через WSAStartup.
     */
    TcpServer(int port);

    /**
     * @brief Деструктор класса.
     * @note Автоматически вызывает stop() и очищает ресурсы Winsock.
     */
    ~TcpServer();

    /**
     * @brief Запуск сервера и ожидание подключения.
     * @details Создает сокет, выполняет bind() и listen(), после чего блокирует
     * выполнение до вызова accept().
     * @return true, если клиент успешно подключился, иначе false.
     */
    bool start();

    /**
     * @brief Остановка сервера.
     * @details Закрывает активные сокеты и сбрасывает флаг работы.
     */
    void stop();

    /**
     * @brief Получение данных от клиента.
     * @return std::string Строка с полученными данными. Если данных нет или 
     * произошла ошибка, возвращает пустую строку.
     */
    std::string receiveData();
};