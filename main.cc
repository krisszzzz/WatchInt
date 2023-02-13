#include <watch_int.h>
#include <logger.h>
#include <func_tracker.h>

void
some_funct()
{
    FUNC_TRACK;

    Logger* logger = Logger::getInstance();

    for ( int i = 0; i < logger->getDepth(); i++ )
    {
        printf( "%s\n", logger->getFunction( i ));
    }
}

int
main()
{
    FUNC_TRACK;
    const char* function = __PRETTY_FUNCTION__;

    printf( "%s %p\n", function, function );


    SET_WATCHINT_BY_VALUE( a, 5 );

    SET_WATCHINT_BY_VAR( b, a );
    SET_WATCHINT_BY_VAR( c, b );
    SET_WATCHINT_BY_VAR( d, b );

    some_funct();
    c = a+b+d;
}
