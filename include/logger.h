#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <string.h>

#define NON_COPYABLE( class_name )      \
    class_name( class_name& ) = delete; \
    void operator=( const class_name& ) = delete

#define MAX_FUNC_DEPTH 128

class Logger
{
public:
    NON_COPYABLE( Logger );

    void makeGraphvizHead() {
    }

    static Logger* getInstance()
    {
        static Logger instance{};
        return &instance;
    }

    void addFunction( const char* func_name )
    {
        functions_[depth_] = func_name;
        depth_++;
    }

    void removeFunction()
    {
        depth_--;
    }

    const char* getFunction( int indx ) const
    {
        return functions_[indx];
    }

    int getDepth() const
    {
        return depth_;
    }

private:
    Logger() : depth_( 0 )
    {
        memset( functions_, 0, MAX_FUNC_DEPTH * sizeof( char* ) );
    };
    // function depth
    int depth_;
    const char* functions_[MAX_FUNC_DEPTH];
};

#endif
