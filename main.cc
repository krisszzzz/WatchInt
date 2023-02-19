#include <watch_int.h>
#include <logger.h>
#include <func_tracker.h>

void
some_funct()
{
    FUNC_TRACK;

    DEF_WATCHINT_BY_VALUE( b, 5 );

}

int
main()
{
    FUNC_TRACK;

    DEF_WATCHINT_BY_VALUE( a, 5 );
    DEF_WATCHINT_BY_VALUE( b, 5 );

    DEF_WATCHINT_BY_VAR( c, b );

    // SET_WATCHINT_BY_VAR( b, a );
    // SET_WATCHINT_BY_VAR( c, b );
    // SET_WATCHINT_BY_VAR( d, b );

    some_funct();
    // c = a+b+d;
}
