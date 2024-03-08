// muce - Motivesoft UCI Chess Engine
// Copyright (c) 2024, Ian Brown

#include <algorithm>
#include <istream>
#include <iostream>
#include <map>
#include <string>

// Used in command parsing
const std::string whitespaces = "\t\n\r\f\v";

// A typedef for methods that take two std::string references and return a boolean
typedef bool (*KeywordHandler)( const std::string&, const std::string& );

// A const array of keywords to KeywordHandler
std::map<std::string, KeywordHandler> handlerMap;

// Keyword handlers
bool processQuit( const std::string& keyword, const std::string& args );
bool processUCI( const std::string& keyword, const std::string& args );

/// <summary>
/// Entrypoint
/// </summary>
/// <param name="argc">Count of command line arguments</param>
/// <param name="argv">Command line arguments</param>
/// <returns>0 if successful</returns>
int main( int argc, char** argv )
{
    handlerMap["quit"] = processQuit;
    handlerMap["uci"] = processUCI;

    // Read from stdin but then sanitize the input
    std::string line;
    while (std::getline(std::cin, line) )
    {
        // Iterator over line and replace any of the following with spaces: \t\n\r\f\v
        for (std::string::iterator it = line.begin(); it != line.end(); ++it)
        {
            if ( whitespaces.find( *it ) != std::string::npos )
            {
                *it = ' ';
            }
        }

        // Change any instance of multiple spaces to single space
        while( line.find( "  " ) != std::string::npos )
        {
            line.replace( line.find( "  " ), 2, " " );
        }

        // Trim leading spaces from line
        line = line.substr(line.find_first_not_of(" "));

        // Trim trailing spaces from line
        line = line.substr(0, line.find_last_not_of(" ")+1);

        // Extract the first word into one string and the remainder into another
        std::string keyword = line.substr(0, line.find_first_of(" "));
        
        // If line has a space, extract the remainder, otherwise leave it blank
        std::string args;
        if ( line.find_first_of( " " ) != std::string::npos )
        {
            args = line.substr( line.find_first_of( " " ) + 1 );
        }

        // Convert the keyword to lowercase
        std::transform( keyword.begin(), keyword.end(), keyword.begin(), ::tolower );

        // Process the keyword and continue until we're told to exit
        if ( handlerMap.find( keyword ) != handlerMap.end() )
        {
            if ( !handlerMap[ keyword ]( keyword, args ) )
            {
                break;
            }
        }
    }

    return 0;
}

bool processQuit( const std::string& keyword, const std::string& args )
{
    return false;
}

bool processUCI( const std::string& keyword, const std::string& args )
{
    return true;
}
