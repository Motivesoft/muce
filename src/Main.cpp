// muce - Motivesoft UCI Chess Engine
// Copyright (c) 2024, Ian Brown

#include <algorithm>
#include <istream>
#include <iostream>
#include <map>
#include <string>

#include "Engine.h"

// Used in command parsing
const std::string whitespaces = "\t\n\r\f\v";

/// <summary>
/// Entrypoint
/// </summary>
/// <param name="argc">Count of command line arguments</param>
/// <param name="argv">Command line arguments</param>
/// <returns>0 if successful</returns>
int main( int argc, char** argv )
{
    // Assume all is well and that we're in UCI mode
    Engine engine( std::cout );

    // Read from stdin but then sanitize the input
    std::string line;
    while ( std::getline( std::cin, line ) )
    {
        // Iterator over line and replace any of the following with spaces: \t\n\r\f\v
        for ( std::string::iterator it = line.begin(); it != line.end(); ++it )
        {
            if ( whitespaces.find( *it ) != std::string::npos )
            {
                *it = ' ';
            }
        }

        // Trim leading spaces from line
        line = line.substr( line.find_first_not_of( " " ) );

        // Trim trailing spaces from line
        line = line.substr( 0, line.find_last_not_of( " " ) + 1 );

        // Change any instance of multiple spaces to single space
        while ( line.find( "  " ) != std::string::npos )
        {
            line.replace( line.find( "  " ), 2, " " );
        }

        // Extract the first word into a lowercase keyword string
        std::string keyword = line.substr( 0, line.find_first_of( " " ) );
        std::transform( keyword.begin(), keyword.end(), keyword.begin(), ::tolower );

        // If line has more text after the keyword, extract the remainder as args, otherwise leave as blank
        std::string arguments;
        if ( line.find_first_of( " " ) != std::string::npos )
        {
            arguments = line.substr( line.find_first_of( " " ) + 1 );
        }

#if __DEBUG
            std::cerr << "Input: " << keyword << " [" << arguments << "]" << std::endl;
#endif 

        // Process the command and loop until we're told to exit
        if ( !engine.processCommand( keyword, arguments ) )
        {
            break;
        }
    }

    return 0;
}
