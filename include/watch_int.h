#ifndef WATCH_INT_H_
#define WATCH_INT_H_

#include <stdio.h>
#include <string.h>
#include <string>

#define SET_WATCHINT_BY_VALUE( name, value ) \
    WatchInt name( value, __LINE__, __PRETTY_FUNCTION__, #name )

#define SET_WATCHINT_BY_VAR( name, var ) \
    WatchInt name( var, __LINE__, __PRETTY_FUNCTION__, #name )


class WatchInt
{
public:

    WatchInt( int value,
              int line,
              const char* function,
              const char* var_name );

    WatchInt& operator=( const WatchInt& that );

    WatchInt( const WatchInt& that,
              int line = 0,
              const char* function = nullptr,
              const char* var_name = nullptr );

    WatchInt& operator+=( const WatchInt& that );
    WatchInt operator+( const WatchInt& that );

private:
    int value_;
    std::string name_;
    // History of created variable
    std::string history_;
};

#endif
