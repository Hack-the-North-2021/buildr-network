#include "NetworkClient.h"

#define PORT 8080
#define MAX_PACKET 1024

NetworkClient::NetworkClient(const std::string& ip_address, int port)
    : port(port)
{

}

NetworkClient::~NetworkClient()
{

}
