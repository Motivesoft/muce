#include "EngineDetails.h"

#define ENGINE_NAME "muce"
#define ENGINE_AUTHOR "Ian Brown"
#define ENGINE_VERSION "0.0.1"

std::string EngineDetails::EngineName()
{
    return ENGINE_NAME;
}

std::string EngineDetails::EngineAuthor()
{
    return ENGINE_AUTHOR;
}

std::string EngineDetails::EngineVersion()
{
    return ENGINE_VERSION;
}
