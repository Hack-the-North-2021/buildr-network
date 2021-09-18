#include "NetworkServer.h"
#include "Logger.h"

int
main(int argc, char** argv)
{
    NetworkServer server(8080); 
    server.OpenConnection();
    
    return 0;
}
