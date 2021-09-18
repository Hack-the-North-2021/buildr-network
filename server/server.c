#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define PORT 8080
#define MAX_PACKET 1024
#define BACKLOG_SIZE 10

typedef struct sockaddr Sockaddr;
typedef struct sockaddr_in SockaddrIn;

void error_die(const char* error_msg);
void* handle_client(void* args);

void
error_die(const char* error_msg)
{
    fprintf(stderr, "%s\n", error_msg);
    exit(1);
}

void*
handle_client(void* args)
{
    char send_data[MAX_PACKET];
    char recv_data[MAX_PACKET];

    int client_sock = *(int*)args;

    snprintf(send_data, MAX_PACKET, "hello client");
    memset(recv_data, 0, MAX_PACKET);

    read(client_sock, recv_data, MAX_PACKET);
    printf("%s\n", recv_data);
    send(client_sock, send_data, strlen(send_data), 0);

}

int main(int argc, char const *argv[])
{
    int server_fd, client_sock;
    SockaddrIn address;
    int addrlen = sizeof(address);
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_die("Cannot create the socket");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    if (bind(server_fd, (Sockaddr*)&address, sizeof(address)) < 0)
        error_die("Cannot bind");

    if (listen(server_fd, BACKLOG_SIZE) < 0)
        error_die("Error listening");

    while (1) {

        printf("Listening to connections on port %d\n", PORT);
        if ((client_sock = accept(server_fd, (Sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
            error_die("Error accepting connection");

        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, &client_sock);

    }

    return 0;
}
