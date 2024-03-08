#pragma once

#include <ostream>

#include "Board.h"

class Perft
{
public:
    Perft( std::ostream& outputStream );

    void runPerft( const std::string& args );

private:
    std::ostream& outputStream;

    Board board;
};

