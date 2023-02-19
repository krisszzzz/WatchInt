#ifndef FUNC_TRACKER_H_
#define FUNC_TRACKER_H_

#include <logger.h>

#define FUNC_TRACK FuncTracker tracker__993__ = __PRETTY_FUNCTION__

// Track current function
class FuncTracker
{
public:

    FuncTracker( const char* func_name )
    {
        Logger* logger = Logger::getInstance();
        logger->addFunction( func_name );
    }

    ~FuncTracker()
    {
        Logger* logger = Logger::getInstance();
        logger->removeFunction();
    }

};

#endif
