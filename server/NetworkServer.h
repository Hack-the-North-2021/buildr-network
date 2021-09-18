#ifndef __NETWORKSERVER_H__
#define __NETWORKSERVER_H__

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#include <thread>
#include <map>

#include "lib/json.hpp"

typedef struct sockaddr Sockaddr;
typedef struct sockaddr_in SockaddrIn;

typedef void (*NetworkCallback)(const nlohmann::json& json_cmd);

class NetworkServer
{
private:
    int server_fd;
    SockaddrIn address;
    int port;
    std::map<int,NetworkCallback> network_callbacks;
public:
    NetworkServer(int port, std::map<int,NetworkCallback> network_callbacks);
    ~NetworkServer();
    void OpenConnection();
 private:
    void Listen();
    void HandleConnection(int client_sock);
    void DispatchCmd(const std::string& json_string);
    void SendRawMessage(int client_sock, const nlohmann::json& data);
};

#endif // __NETWORKSERVER_H__
