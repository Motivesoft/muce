#pragma once

class Board
{
public:
    // Singleton
    static Board& getInstance()
    {
        static Board instance;

        return instance;
    }

private:
    // Private constructor to prevent instantiation
    Board()
    {
    }

    // Delete the copy constructor and assignment operator
    Board(const Board&) = delete;
};

