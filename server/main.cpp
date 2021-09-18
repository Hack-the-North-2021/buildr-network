#include "NetworkServer.h"
#include "Logger.h"

void cb(const nlohmann::json& json_cmd) {
    Logger::Debug("DID IT!");
}

int
main(int argc, char** argv)
{
    std::map<int,NetworkCallback> network_callbacks = {
        {1, cb}
    };
    NetworkServer server(8080, network_callbacks); 
    server.OpenConnection();
    
    return 0;
}
