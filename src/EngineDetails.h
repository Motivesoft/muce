#pragma once

#include <string>

class EngineDetails
{
    // Create a singleton instance
public: 
    // Create methods to return engine details
    static std::string EngineName();
    static std::string EngineAuthor();
    static std::string EngineMajorVersion();
    static std::string EngineVersion();

private:
    // Private constructor
    EngineDetails();
};

