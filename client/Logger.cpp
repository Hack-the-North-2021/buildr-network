#include <cstdio>

#include "Logger.h"

void
Logger::ErrorDie(const std::string& message)
{
    fprintf(stderr, "[ERROR] %s\n", message.c_str());
    exit(1);
}

void
Logger::Network(const std::string& message)
{
    printf("[NETWORK] %s\n", message.c_str());
}
