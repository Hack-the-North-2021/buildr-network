
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
