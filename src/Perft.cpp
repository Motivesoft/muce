#include "Perft.h"

#if _DEBUG
#include <iostream>
#endif

Perft::Perft( std::ostream& outputStream ) :
    board( Board() ),
    outputStream( outputStream )
{
    // Constructor
}

void Perft::runPerft( const std::string& args )
{
    // Initialise defaults
    int depth = 1;
    std::string position = "";
    std::string expected = "";
    
    // Supported syntax is:
    // perft <depth>
    // perft <depth> <position>
    // perft fen <position> <expected>
    // perft fen <position>
    // perft file <filename>

    // Parse args to extract the first word
    std::string command = args.substr( 0, args.find_first_of( " " ) );

    // If the first word is a number, extract the value into depth, otherwise, see if the value is 'fen' or 'file' and handle each case
    if ( command == "fen" )
    {
        position = args.substr( args.find_first_of( " " ) + 1, args.find_first_of( " " ) );
    }
    else if ( command == "file" )
    {
        std::string file = args.substr( args.find_first_of( " " ) + 1, args.find_first_of( " " ) );
    }
    else if ( std::isdigit( command[ 0 ] ) )
    {
        depth = std::stoi( command );
    }

    // Ignore empty strings
    if ( args.length() == 0 )
    {
        return;
    }

    // Parse arguments to get depth, position, etc.
    if( std::isdigit( args[ 0 ] ) )
    {
        // Extract the first word from args and convert it to an int
        depth = std::stoi( args.substr( 0, args.find_first_of( " " ) ) );

        if ( args.find_first_of( " " ) != std::string::npos )
        {
            // Extract the next parts of the string up to the next comma or semicolon
            position = args.substr( args.find_first_of( " " ) + 1, args.find_first_of( ",;" ) - args.find_first_of( " " ) - 1 );

            if ( args.find_first_of( ",;" ) != std::string::npos )
            {
                // Extract the remaining parts of the string
                expected = args.substr( args.find_first_of( ",;" ) + 1 );
            }
        }
    }

    // Print each element separately
#if _DEBUG
    std::cerr << "Depth: [" << depth << "]" << std::endl;
    std::cerr << "Position: [" << position << "]" << std::endl;
    std::cerr << "Expected: [" << expected << "]" << std::endl;
#endif
}
