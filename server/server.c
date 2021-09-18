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
    int client_handle;
    struct sockaddr_in addr;

    if ((client_handle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_die("Cannot create the socket");

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVER_PORT);

    if (bind(client_handle, (struct sockaddr_in*)&addr, sizeof(addr)) < 0)
        error_die("Cannot bind");

    if (listen(client_handle, 10) < 0)
        error_die("Error listening");

    return 0;
}

