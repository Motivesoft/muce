#pragma once

#include <string>

class Board
{
public:
    // Constructor
    Board();

    void perft( const std::string& args );

private:
    // Delete the copy constructor and assignment operator
    Board(const Board&) = delete;
};

