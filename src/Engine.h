#pragma once

#include <map>
#include <ostream>

#include "Board.h"

class Engine
{
public:
    // Private constructor to prevent instantiation
    Engine( std::ostream& outputStream ) :
        board( Board() ),
        outputStream( outputStream )
    {
        handlerMap["quit"] = &Engine::processQuit;
        handlerMap["uci"] = &Engine::processUCI;
    }

    // A typedef for methods that take two std::string references and return a boolean
    typedef bool ( Engine::*KeywordHandler )( const std::string&, const std::string& );

    bool processCommand( const std::string& keyword, const std::string& args );

private:
    // Delete the copy constructor and assignment operator
    Engine( const Engine& ) = delete;

    // Single board instance for this engine instance
    Board board;

    // Use to communicate back to the caller
    std::ostream& outputStream;

    // A const array of keywords to KeywordHandler
    std::map<std::string, KeywordHandler> handlerMap;

    // Keyword handlers
    bool processQuit( const std::string& keyword, const std::string& args );
    bool processUCI( const std::string& keyword, const std::string& args );

    // Helper functions
    void sendID( const std::string& name, const std::string& author, const std::string& version );
};