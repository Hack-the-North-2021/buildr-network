#include <cstdio>

#include "Logger.h"

void
Logger::ErrorDie(const std::string& message)
{
    fprintf(stderr, "%s\n", message.c_str());
    exit(1);
}
