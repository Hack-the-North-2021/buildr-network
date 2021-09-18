#include <cstdio>
#include <cstring>

#include "NetworkClient.h"
#include "Logger.h"

#define MAX_PACKET 1024

NetworkClient::NetworkClient(std::string ip_address, int port)
    : ip_address(ip_address), port(port)
{

}

NetworkClient::~NetworkClient()
{

}

void
NetworkClient::OpenConnection()
{
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        Logger::ErrorDie("Cannot create the socket");
   
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_address.c_str(), &address.sin_addr) <= 0) 
        Logger::ErrorDie("Invalid IP Address");
   
    if (connect(client_fd, (Sockaddr*)&address, sizeof(address)) < 0)
        Logger::ErrorDie("Connection failed");

    std::thread worker(&NetworkClient::HandleConnection, this);

    worker.join();
}

void
NetworkClient::HandleConnection()
{
    char recv_msg[MAX_PACKET];
    int read_size;

    Logger::Network("Connection to server established");
    while (true) {
        memset(recv_msg, 0, MAX_PACKET);
        if ((read_size = read(client_fd, recv_msg, MAX_PACKET)) <= 0)
            continue;

        Logger::Debug(std::string(recv_msg));
    }
}

void
NetworkClient::SendRawMessage()
{
    /* take in json object */
    std::string message = "lmao";
    const char* send_data = message.c_str();
    int data_len = strlen(send_data);

    if (data_len > MAX_PACKET)
        Logger::Warning("Attempting to send a packet exceeding max size");

    send(client_fd, send_data, data_len, 0);
    Logger::Debug("Sent message");
}

