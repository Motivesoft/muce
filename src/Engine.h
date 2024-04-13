#pragma once

#include <map>
#include <ostream>

#include "Board.h"

class Engine
{
public:
    // Constructor
    Engine( std::ostream& outputStream );

    // A typedef for methods that take two std::string references and return a boolean
    typedef bool ( Engine::* KeywordHandler )( const std::string&, const std::string& );

    bool processCommand( const std::string& keyword, const std::string& args );

    enum class RegistrationStatus
    {
        Checking,
        OK,
        Error
    };

private:
    // Delete the copy constructor and assignment operator
    Engine( const Engine& ) = delete;

    // Single board instance for this engine instance
    Board board;

    // Use to communicate back to the caller
    std::ostream& outputStream;

    // A const array of keywords to KeywordHandler
    std::map<std::string, KeywordHandler> handlerMap;

    // Registration status
    RegistrationStatus registrationStatus;

    // UCI Keyword handlers
    bool processQuit( const std::string& keyword, const std::string& args );
    bool processUCI( const std::string& keyword, const std::string& args );
    bool processIsReady( const std::string& keyword, const std::string& args );
    bool processUCINewGame( const std::string& keyword, const std::string& args );

    // Unofficial keyword handlers
    bool processPerft( const std::string& keyword, const std::string& args );

    // Broadcast functions
    void sendID( const std::string& name, const std::string& author, const std::string& version );
    void sendUCIOK();
    void sendReadyOK();
    void sendInfo( const std::string& info );
    void sendRegistration( const RegistrationStatus status );

    // Helper functions
    void setRegistrationStatus( RegistrationStatus status );

    const std::map<RegistrationStatus, std::string> statusMap = 
    {
        { RegistrationStatus::Checking, "checking" },
        { RegistrationStatus::OK, "ok" },
        { RegistrationStatus::Error, "error" }
    };
};