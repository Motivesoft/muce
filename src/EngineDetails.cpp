#include "EngineDetails.h"

#define ENGINE_NAME "muce"
#define ENGINE_AUTHOR "Ian Brown"
#define ENGINE_MAJOR_VERSION "0"
#define ENGINE_MINOR_VERSION "0"
#define ENGINE_POINT_VERSION "1"

std::string EngineDetails::EngineName()
{
    return ENGINE_NAME;
}

std::string EngineDetails::EngineAuthor()
{
    return ENGINE_AUTHOR;
}

std::string EngineDetails::EngineMajorVersion()
{
    return ENGINE_MAJOR_VERSION;
}

std::string EngineDetails::EngineVersion()
{
    return EngineMajorVersion() + "." + ENGINE_MINOR_VERSION + "." + ENGINE_POINT_VERSION;
}
