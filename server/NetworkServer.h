#ifndef __NETWORKSERVER_H__
#define __NETWORKSERVER_H__

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#include <thread>

typedef struct sockaddr Sockaddr;
typedef struct sockaddr_in SockaddrIn;

class NetworkServer
{
private:
    int server_fd;
    SockaddrIn address;
    int port;
public:
    NetworkServer(int port);
    ~NetworkServer();
    void OpenConnection();
 private:
    void Listen();
    void HandleConnection(int client_sock);
};

#endif // __NETWORKSERVER_H__
