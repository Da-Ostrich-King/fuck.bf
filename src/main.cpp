

#include <vector>
#include <fstream>
#include <string>

enum Instruction {
    TAPE_LEFT = '<',
    TAPE_RIGHT = '>',
    INCREMENT = '+',
    DECREMENT = '-',
    PUTCHAR = '.',
    GETCHAR = ',',
    LOOP_OPEN = '[',
    LOOP_CLOSE = ']',
    IF_OPEN = '(',
    IF_CLOSE = ')',
};

void runProgram( std::vector< Instruction > program ) {
    int programCounter;
    int memAddr;
    std::vector< uint_least8_t > tape;
}



int main( int argc, char** argv ) {
    std::vector< Instruction > program;

    if ( argc < 2 ) {
        exit( 1 );
    } else if ( argc > 2 ) {
        exit ( 1 );
    }

    std::fstream file( argv[ 1 ] );

    char instruction;
    while ( file.get( instruction ) ) {
        switch ( instruction ) {
        case TAPE_LEFT:
            program.push_back( TAPE_LEFT );
            break;
        case TAPE_RIGHT:
            program.push_back( TAPE_RIGHT);
            break;
        case INCREMENT:
            program.push_back( INCREMENT );
            break;
        case DECREMENT:
            program.push_back( DECREMENT );
            break;
        case PUTCHAR:
            program.push_back( PUTCHAR );
            break;
        case GETCHAR:
            program.push_back( GETCHAR );
            break;
        case LOOP_OPEN:
            program.push_back( LOOP_OPEN );
            break;
        case LOOP_CLOSE:
            program.push_back( LOOP_CLOSE );
            break;
        case IF_OPEN:
            program.push_back( IF_OPEN );
            break;
        case IF_CLOSE:
            program.push_back( IF_CLOSE );
            break;
        default:
            break;
        }
    }
    
    runProgram( program );

    return 0;
}