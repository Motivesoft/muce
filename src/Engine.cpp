#include <iostream>

#include "Engine.h"
#include "EngineDetails.h"

bool Engine::processCommand( const std::string& keyword, const std::string& args )
{
    // Process the keyword and continue until we're told to exit
    if ( handlerMap.find( keyword ) != handlerMap.end() )
    {
        auto handler = handlerMap.at( keyword );

        return (*this.*handler)( keyword, args );
    }
#if _DEBUG
    else
    {
        std::cerr << "Unknown command: " << keyword << std::endl;
    }
#endif

    // By default, return true to continue processing
    return true;
}

bool Engine::processQuit( const std::string& keyword, const std::string& args )
{
#if _DEBUG
    std::cerr << "Quit" << std::endl;
#endif

    // TODO Shutdown everything and prepare to exit

    return false;
}

bool Engine::processUCI( const std::string& keyword, const std::string& args )
{
#if _DEBUG
    std::cerr << "UCI" << std::endl;
#endif

    sendID( EngineDetails::EngineName(), EngineDetails::EngineAuthor(), EngineDetails::EngineVersion() );

    return true;
}

void Engine::sendID( const std::string& name, const std::string& author, const std::string& version )
{
    outputStream << "id name " << name << " " << version << std::endl;
    outputStream << "id author " << author << std::endl;
}
