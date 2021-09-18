#include <cstdio>

#include "Logger.h"

/* delete this line to turn off debug messages */
#define DEBUG_MODE

void
Logger::ErrorDie(const std::string& message)
{
    fprintf(stderr, "[ERROR] %s\n", message.c_str());
    exit(1);
}

void
Logger::Network(const std::string& message)
{
    #ifdef DEBUG_MODE
    printf("[NETWORK] %s\n", message.c_str());
    #endif
}

void
Logger::Warning(const std::string& message)
{
    #ifdef DEBUG_MODE
    printf("[WARN] %s\n", message.c_str());
    #endif
}

void
Logger::Debug(const std::string& message)
{
    #ifdef DEBUG_MODE
    printf("[DEBUG] %s\n", message.c_str());
    #endif
}
