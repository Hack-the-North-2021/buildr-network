#include <cstring>

#include "NetworkServer.h"
#include "Logger.h"

#define MAX_PACKET 1024
#define BACKLOG_SIZE 10

NetworkServer::NetworkServer(int port, std::map<int,NetworkCallback> network_callbacks)
    : server_fd(0), port(port), network_callbacks(network_callbacks)
{

}

NetworkServer::~NetworkServer()
{

}

void
NetworkServer::OpenConnection()
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        Logger::ErrorDie("Cannot create the socket");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
       
    if (bind(server_fd, (Sockaddr*)&address, sizeof(address)) < 0)
        Logger::ErrorDie("Cannot bind");

    if (listen(server_fd, BACKLOG_SIZE) < 0)
        Logger::ErrorDie("Error listening");

    std::thread worker(&NetworkServer::Listen, this);

    worker.join();
}

void
NetworkServer::Listen()
{
    int client_sock;
    int addrlen = sizeof(address);

    while (true) {
        Logger::Debug("Listening to connections");
        if ((client_sock = accept(server_fd, (Sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
            Logger::ErrorDie("Error accepting connection");

        std::thread worker(&NetworkServer::HandleConnection, this, client_sock);

        worker.join();
    }
}

void
NetworkServer::HandleConnection(int client_sock)
{
    char recv_msg[MAX_PACKET];
    int read_size;

    Logger::Network("Connection established with client");
    while (true) {
        memset(recv_msg, 0, MAX_PACKET);
        if ((read_size = read(client_sock, recv_msg, MAX_PACKET)) <= 0)
            continue;

        Logger::Debug(std::string(recv_msg));
        DispatchCmd(recv_msg);
    }
}

void
NetworkServer::DispatchCmd(const std::string& json_string)
{
    try {
        nlohmann::json data = nlohmann::json::parse(json_string);
        int cmd = data["cmd"];

        for (const auto &[nc_cmd, nc_callback] : network_callbacks) {
            if (cmd != nc_cmd) continue;
            
            nc_callback(cmd);
        }

    } catch (nlohmann::json::parse_error& e) {
        Logger::Warning("Malformed json string");
    }
}

void
NetworkServer::SendRawMessage(int client_sock, const nlohmann::json& data)
{
    std::string serialized = data.dump();
    const char* send_data = serialized.c_str();
    int data_len = strlen(send_data);

    if (data_len > MAX_PACKET)
        Logger::Warning("Attempting to send a packet exceeding max size");

    send(client_sock, send_data, data_len, 0);
    Logger::Debug("Sent message");
}

