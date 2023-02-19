#ifndef WATCH_INT_H_
#define WATCH_INT_H_

#include <stdio.h>
#include <string.h>
#include <string>

#define DEF_WATCHINT_BY_VALUE( name, value ) \
    WatchInt name( value, #name )

#define DEF_WATCHINT_BY_VAR( name, var ) \
    WatchInt name( var, #name )

#define ASSIGN_WATCHINT( name, var ) \
    name.operator=( var, __LINE__, __PRETTY_FUNCTION__, #name )


class WatchInt
{
public:

    WatchInt( int value,
              const char* var_name );

    WatchInt& operator=( const WatchInt& that );

    WatchInt( const WatchInt& that,
              const char* var_name = nullptr );

    WatchInt& operator+=( const WatchInt& that );
    WatchInt operator+( const WatchInt& that );

    int getValue() const
    {
        return value_;
    }

    // std::string& getName()
    // {
    //     return name_;
    // }

private:
    int value_;
    // std::string name_;
    // History of created variable
};

#endif
