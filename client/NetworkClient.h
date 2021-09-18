#include <string>

typedef struct sockaddr Sockaddr;
typedef struct sockaddr_in SockaddrIn;

class NetworkClient
{
private:
    int client_fd;
    SockaddrIn address;
    int port;
public:
    NetworkClient(const std::string& ip_address, int port);
    ~NetworkClient();
};
