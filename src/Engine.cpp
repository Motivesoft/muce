#include <iostream>

#include "Engine.h"
#include "EngineDetails.h"

Engine::Engine( std::ostream& outputStream ) :
    board( Board() ),
    outputStream( outputStream )
{
    handlerMap[ "quit" ] = &Engine::processQuit;
    handlerMap[ "uci" ] = &Engine::processUCI;
    handlerMap[ "perft" ] = &Engine::processPerft;

    sendInfo( "Starting " + EngineDetails::EngineName() + " " + EngineDetails::EngineMajorVersion() );
}

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

    // TODO send options
    // TODO copy protection and/or registration

    sendUCIOK();

    return true;
}

bool Engine::processPerft( const std::string& keyword, const std::string& args )
{
#if _DEBUG
    std::cerr << "Perft" << std::endl;
#endif

    return true;
}

void Engine::sendID( const std::string& name, const std::string& author, const std::string& version )
{
    outputStream << "id name " << name << " " << version << std::endl;
    outputStream << "id author " << author << std::endl;
}

void Engine::sendUCIOK()
{
    outputStream << "uciok" << std::endl;
}

void Engine::sendReadyOK()
{
    outputStream << "readyok" << std::endl;
}

void Engine::sendInfo( const std::string& info )
{
    outputStream << "info string " << info << std::endl;
}
