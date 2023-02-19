#ifndef LOGGER_H_
#define LOGGER_H_

#include "watch_int.h"
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

    void makeGraphvizSubgraph( const char* function_name )
    {
        static int cluster_count = 0;

        fprintf( file_, "subgraph cluster_%d {\n", cluster_count );
        fprintf( file_, "label = \"%s\"\n", function_name );

        cluster_count++;
    }


    void addNode( const char* var_name,
                  const WatchInt* this_watch_int,
                  const char* color )
    {
        fprintf( file_,
                 "%lu [shape = \"none\" label = <<table border = \"1\" "
                 "bgcolor = \"%s\">\n"
                 "<tr><td>name</td><td>%s</td></tr>\n"
                 "<tr><td>value</td><td>%d</td></tr>\n"
                 "<tr><td>address</td><td>%p</td></tr></table>>]\n",
                 (uint64_t) this_watch_int,
                 color,
                 var_name,
                 this_watch_int->getValue(),
                 this_watch_int );
    }

    // add node that define how the object was created, moved, etc..
    void addOperationNode( const WatchInt* this_watch_int,
                           const char* operation_name )
    {
        fprintf( file_,
                 "%s_%lu [shape = \"circle\" label = %s color = \"green\"]\n",
                 operation_name,
                 (uint64_t) this_watch_int,
                 operation_name );
    }

    void addConstructorNode( const char* this_watch_int_name,
                             WatchInt* this_watch_int )
    {
        addObjectNode( this_watch_int_name, this_watch_int );
        addOperationNode( this_watch_int, "Ctor" );

        fprintf( file_,
                 "Ctor_%lu -> %lu\n",
                 (uint64_t) this_watch_int,
                 (uint64_t) this_watch_int );
    }

    void addCopyCtorNode( const char* this_watch_int_name,
                          const WatchInt* this_watch_int,
                          const WatchInt* that_watch_int )
    {
        addObjectNode( this_watch_int_name, this_watch_int );
        addOperationNode( this_watch_int, "CopyCtor" );

        fprintf( file_,
                 "%lu -> CopyCtor_%lu -> %lu\n",
                 (uint64_t) that_watch_int,
                 (uint64_t) this_watch_int,
                 (uint64_t) this_watch_int );

    }

    // For temporary object

    void addTempObjectNode( const char* var_name,
                            const WatchInt* this_watch_int )
    {
        addNode( var_name, this_watch_int, "red" );
    }

    // For non-temporary object
    void addObjectNode( const char* var_name,
                        const WatchInt* this_watch_int )
    {
        addNode( var_name, this_watch_int, "green" );
    }

    void closeBrace()
    {
        fprintf( file_, "}\n" );
    }

    static Logger* getInstance()
    {
        static Logger instance{};
        return &instance;
    }

    void addFunction( const char* func_name )
    {
        makeGraphvizSubgraph( func_name );
    }

    void removeFunction()
    {
        closeBrace();
    }


private:

    void makeGraphvizDigraph()
    {
        fprintf( file_, "digraph {\n" );
    }

    Logger() : file_( 0 )
    {
        file_ = fopen( "log.gv", "w" );

        if ( file_ == nullptr )
        {
            fprintf( stderr, "log file open error\n" );
        }

        makeGraphvizDigraph();

    };

    ~Logger()
    {
        closeBrace();

        fclose( file_ );
        file_ = nullptr;

    }

    // Members

    FILE* file_;
};

#endif
