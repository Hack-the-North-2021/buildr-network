#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define MAX_PACKET 4096

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
    int socket_handle;
    struct sockaddr_in addr;

    if (socket_handle = socket(AF_INET, SOCK_STREAM, 0) < 0)
        error_die("Cannot create the socket");

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
        error_die("Invalid IP Address");

    if (connect(socket_handle, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        error_die("Connection failed");

    return 0;
}
