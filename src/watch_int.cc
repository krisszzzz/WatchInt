#include <watch_int.h>
#include <logger.h>
#include <func_tracker.h>

WatchInt::WatchInt( int value,
                    int line,
                    const char* function,
                    const char* var_name ) :
    value_( value ),
    name_( var_name )
{
    char info[128] = { 0 };

    sprintf( info,
             "WatchInt %s [%p] = %d created on %s:%d\n",
             var_name, this, value, function, line );

    history_.append( info );
    printf( history_.c_str());

}

WatchInt&
WatchInt::operator=( const WatchInt& that )
{
    printf( "operator=\n" );
    value_ = that.value_;
    history_ = that.history_;

    return *this;
}

WatchInt::WatchInt( const WatchInt& that,
                    int line,
                    const char* function,
                    const char* var_name )
{
    value_ = that.value_;

    if ( line == 0 &&
         function == nullptr &&
         var_name == nullptr )
    {
        printf( "Cringe!\n" );
        return;
    }


    name_.append( var_name );

    char info[128] = { 0 };

    sprintf( info,
             "WatchInt %s [%p] = %s created on %s:%d\n",
             var_name, this, that.name_.c_str(), function, line );

    history_.append( info );
    history_.append( that.history_ );

    printf( "_______________________________\n" );
    printf( history_.c_str());
    printf( "_______________________________\n" );
}


WatchInt&
WatchInt::operator+=( const WatchInt& that )
{
    value_ += that.value_;


    printf( "_______________________________\n" );
    printf( "%s += %s\n"
            "%s%s",
            name_.c_str(),    that.name_.c_str(),
            history_.c_str(), that.history_.c_str());
    printf( "_______________________________\n" );

    return *this;
}

WatchInt
WatchInt::operator+( const WatchInt& that )
{
    SET_WATCHINT_BY_VALUE( tmp,
                           this->value_+that.value_ );
    return tmp;
}


