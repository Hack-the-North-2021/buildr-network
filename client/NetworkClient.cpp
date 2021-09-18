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

    std::thread worker(&NetworkClient::Listen, this);

    worker.join();
}

void
NetworkClient::Listen()
{
    Logger::Network("Connection to server established");
    while (true) {

    }
}
