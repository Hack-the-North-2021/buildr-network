#include <thread>

#include "NetworkServer.h"

#define MAX_PACKET 1024
#define BACKLOG_SIZE 10

NetworkServer::NetworkServer(int port)
    : server_fd(0), port(port)
{

}

NetworkServer::~NetworkServer()
{

}

void
NetworkServer::OpenConnection()
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_die("Cannot create the socket");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
       
    if (bind(server_fd, (Sockaddr*)&address, sizeof(address)) < 0)
        error_die("Cannot bind");

    if (listen(server_fd, BACKLOG_SIZE) < 0)
        error_die("Error listening");

    std::thread worker(&NetworkServer::Listen);
}

void
NetworkServer::Listen()
{
    int client_sock;
    int addrlen = sizeof(address);

    while (true) {
        printf("Listening to connections on port %d\n", PORT);
        if ((client_sock = accept(server_fd, (Sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
            error_die("Error accepting connection");

        std::thread worker(&NetworkServer::HandleConnection, client_sock)
    }
}

void
NetworkServer::HandleConnection(int client_sock)
{

}

