#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define MAX_PACKET 4096

typedef struct sockaddr Sockaddr;
typedef struct sockaddr_in SockaddrIn;

void error_die(const char* error_msg);

void
error_die(const char* error_msg)
{
    fprintf(stderr, "%s\n", error_msg);
    exit(1);
}

int
main(int argc, char** argv)
{
    int client_handle;
    int connection_handle;
    SockaddrIn addr;

    if ((client_handle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_die("Cannot create the socket");

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVER_PORT);

    if (bind(client_handle, (Sockaddr*)&addr, sizeof(addr)) < 0)
        error_die("Cannot bind");

    if (listen(client_handle, 10) < 0)
        error_die("Error listening");

    while (1) {
        SockaddrIn addr;
        socklen_t addr_len;
        char client_addr[MAX_PACKET];

        printf("Listening for connections on port %d\n", SERVER_PORT);
        connection_handle = accept(client_handle, (Sockaddr*)&addr, &addr_len);

        inet_ntop(AF_INET, &addr, client_addr, MAX_PACKET-1);
        printf("Client connected: %s\n", client_addr);

        /* read from client */
        int send_len, n;
        char send_data[MAX_PACKET];
        char recv_data[MAX_PACKET];

        memset(recv_data, 0, MAX_PACKET);
        n = read(client_handle, recv_data, MAX_PACKET-1);
        while ((n = read(client_handle, recv_data, MAX_PACKET-1)) > 0) {
            printf("%s\n", recv_data);
            memset(recv_data, 0, MAX_PACKET);
        }
        if (n < 0) {
            printf("%d\n", errno);
            error_die("Error reading client message");
        }
        
        snprintf(send_data, MAX_PACKET, "hello client");
        send_len = strlen(send_data);
        if (write(client_handle, send_data, send_len) != send_len)
            error_die("Error writing to socket handle");
    }

    return 0;
}

