#include "default_include.hpp"

namespace amber{
    // namespace for helper utils of the project
    namespace utils{
        inline void Error( const char *msg ){
            fprintf( stderr, "Error:%s\n",msg );
            exit( -1 );
        }
        
        inline void Assert( bool exp ){
            if( !exp ) Error( "AssertError" );
        }
        
        inline void Assert( bool exp, const char *msg ){
            if( !exp ) Error( msg );
        }

        inline void Warning( const char *msg ){
            fprintf( stderr, "warning:%s\n",msg );
        }
    };    
};