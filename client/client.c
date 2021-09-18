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
    int server_handle;
    SockaddrIn addr;

    if ((server_handle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_die("Cannot create the socket");

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
        error_die("Invalid IP Address");

    if (connect(server_handle, (Sockaddr*)&addr, sizeof(addr)) < 0)
        error_die("Connection failed");

    /* send message to server */
    int send_len, n;
    char send_data[MAX_PACKET];
    char recv_data[MAX_PACKET];

    snprintf(send_data, MAX_PACKET, "hello server");
    send_len = strlen(send_data);
    if (write(server_handle, send_data, send_len) != send_len)
        error_die("Error writing to socket handle");

    /* read response from server */
    memset(recv_data, 0, MAX_PACKET);
    while ((n = read(server_handle, recv_data, MAX_PACKET-1)) > 0) {
        printf("%s", recv_data);
        memset(recv_data, 0, MAX_PACKET);
    }
        
    return 0;
}
