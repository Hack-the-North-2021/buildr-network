#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
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
    int client_fd;
    SockaddrIn address;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_die("Cannot create the socket");
   
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) 
        error_die("Invalid IP Address");
   
    if (connect(client_fd, (Sockaddr*)&address, sizeof(address)) < 0)
        error_die("Connection failed");

    char send_data[MAX_PACKET];
    char recv_data[MAX_PACKET];

    snprintf(send_data, MAX_PACKET, "hello server");

    send(client_fd, send_data, strlen(send_data), 0);
    read(client_fd, recv_data, MAX_PACKET);
    printf("%s\n", recv_data);

    return 0;
}
