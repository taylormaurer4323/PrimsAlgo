#include "debug.h"
#include <iostream>




debug::debug()
{
    verboseDebugOn = false;
    nonVerboseMode = false;
}

debug::debug(bool b_debugMode)
{
    verboseDebugOn =b_debugMode;
}

void debug::debugPrint(const char * debugMessage)
{
    if(verboseDebugOn){
        std::cout<<debugMessage<<std::endl;
        
    }
}
    
void debug::debugPrint(const std::string debugMessage)
{
    if(verboseDebugOn){
    std::cout<<debugMessage<<std::endl;
    }
}

const bool debug::getDebugMode()
{
    return verboseDebugOn;
}
bool debug::nonVerboseModeOn()
{
    return nonVerboseMode;
}
void debug::setDebugMode(int debugMode)
{
    if(debugMode == 1)
    {
        verboseDebugOn = true;
        nonVerboseMode = true;
    }
    else if(debugMode == 2)
    {
        nonVerboseMode = true;
    }
}