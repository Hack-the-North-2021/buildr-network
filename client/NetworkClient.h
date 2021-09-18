#ifndef __NETWORKCLIENT_H__
#define __NETWORKCLIENT_H__

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include <string>
#include <thread>

typedef struct sockaddr Sockaddr;
typedef struct sockaddr_in SockaddrIn;

class NetworkClient
{
private:
    int client_fd;
    SockaddrIn address;
    std::string ip_address;
    int port;
public:
    NetworkClient(std::string ip_address, int port);
    ~NetworkClient();
    void OpenConnection();
    void SendRawMessage();
private:
    void HandleConnection();
};

#endif // __NETWORKCLIENT_H__
