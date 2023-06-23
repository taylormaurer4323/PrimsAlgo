#include <string>

#ifndef DEBUG_H
#define DEBUG_H
class debug{
public:
    debug();
    debug(bool b_debugMode);
    void debugPrint(const char * debugMessage);
    void debugPrint(const std::string message);
    void setDebugMode(int b_debugMode);
    const bool getDebugMode();
    bool nonVerboseModeOn();
    
    
private:
    bool verboseDebugOn;
    bool nonVerboseMode;
    
    
    
    
};



#endif
