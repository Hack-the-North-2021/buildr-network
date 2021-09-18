#include "NetworkClient.h"

int
main(int argc, char** argv)
{
    NetworkClient client("127.0.0.1", 8080); 
    client.OpenConnection();

    return 0;
}
