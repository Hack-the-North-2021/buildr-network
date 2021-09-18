#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define MAX_PACKET 1024

typedef struct sockaddr Sockaddr;
typedef struct sockaddr_in SockaddrIn;

void error_die(const char* error_msg);

void
error_die(const char* error_msg)
{
    fprintf(stderr, "%s\n", error_msg);
    exit(1);
}

int main(int argc, char const *argv[])
{
    int server_fd, client_sock;
    SockaddrIn address;
    int addrlen = sizeof(address);
    int opt = 1;
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_die("Cannot create the socket");
       
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        error_die("setsockopt");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    if (bind(server_fd, (Sockaddr*)&address, sizeof(address)) < 0)
        error_die("Cannot bind");

    if (listen(server_fd, 3) < 0)
        error_die("Error listening");

    if ((client_sock = accept(server_fd, (Sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
        error_die("Error accepting connection");

    char send_data[MAX_PACKET];
    char recv_data[MAX_PACKET];

    snprintf(send_data, MAX_PACKET, "hello client");

    read(client_sock, recv_data, MAX_PACKET);
    printf("%s\n", recv_data);
    send(client_sock, send_data, strlen(send_data), 0);

    return 0;
}
