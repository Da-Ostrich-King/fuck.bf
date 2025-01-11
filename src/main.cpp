

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <iostream>


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

void runProgram( const std::vector< Instruction > program ) {
    /*
    ** Pointer (index of vecter) to the current instruction of the bf program
    */
    uint32_t programCounter = 0;

    /*
    ** Current selected memory address from the perspective of the program.
    */
    int memAddr = 0;

    /*
    ** Offset is to allow negative memory addresses
    */
    int offset = 0;

    /*
    ** The tape is the program memory.
    */
    std::vector< int > tape = { 0 };

    /*
    ** Loop stack is a list of addresses to return to when finishing loop execution.
    ** It has stack semantics, the last in is the current loop, and the first in is the one at the top of the recursion stack
    */
    std::vector< uint32_t > loopStack;

    /*
    ** Beginning of actual program execution
    */
    while ( programCounter < program.size() ) {

        /*
        ** The cerr statement is for debugging purposes.
        */

        /*
        std::cerr << "Executing instruction: '" << ( char ) program[ programCounter ] << ":" << programCounter + 1 << "'\n";
        */
        switch ( program[ programCounter ] ) {
        case TAPE_LEFT:
            memAddr--;
            if ( memAddr + offset < 0 ) {
                tape.insert( tape.begin(), 0 );
                offset++;
            }
            
            break;
        
        case TAPE_RIGHT:

            /*
            ** See `case TAPE_LEFT` for details
            */
            memAddr++;
            if ( tape.size() <= memAddr + offset ) {
                tape.push_back( 0 );
            }
            break;
        case INCREMENT:

            /*
            ** Increment the current memory address.
            ** Buffer overflows and underflows are explicitely allowed and required
            */
            tape[ memAddr + offset ]++;
            break;
        case DECREMENT:

            /*
            ** See `case INCREMENT` for details
            */
            tape[ memAddr + offset ]--;
            break;
        case PUTCHAR:

            /*
            ** Print the ascii character at the current memory address.
            */
            std::cout << ( tape[ memAddr + offset ] == 10 ? '\n' : ( char ) tape[ memAddr + offset ] );
            break;
        case GETCHAR:

            /*
            ** Get the current char from stdin and place the ascii value in the current memory address 
            */
            char buff;
            std::cin >> buff;

            /*
            ** If it is a newline, than make it ascii code 10 as per the standard.
            ** Else set it buff
            */
            if ( buff == '\n' ) {
                tape[ memAddr + offset ] = 10;
            } else {
                tape[ memAddr + offset ] = buff;
            }
            break;
        case LOOP_OPEN:
            if ( tape[ memAddr + offset ] == 0 ) {
                int openLoops = 0;
                for ( int i = programCounter + 1; i < program.size(); i++ ) {                    
                    if ( program[ i ] == LOOP_OPEN ) {
                        openLoops++;
                    } else if ( program[ i ] == LOOP_CLOSE ) {
                        if ( openLoops == 0 ) {
                            programCounter = i + 1;
                            break;
                        } else {
                            openLoops--;
                        }
                    }
                }
            } else {
                loopStack.push_back( programCounter );
            }
            break;
        case LOOP_CLOSE:
            if ( tape[ memAddr + offset ] == 0 ) {
                loopStack.pop_back();
            } else {
                programCounter = loopStack[ loopStack.size() - 1 ];
            }
            break;
        case IF_OPEN:
            break;
        case IF_CLOSE:
            break;
        default:
            throw std::runtime_error( "Invalid instruction" );
            break;
        }

        /*
        ** Increment program counter to point to the next instruction
        */
        programCounter++;
    }
}



int main( int argc, char** argv ) {

    /*
    ** Prospective program
    */
    std::vector< Instruction > program;

    /*
    ** Command-line arg parsing (Incomplete)
    */
    if ( argc < 2 ) {
        exit( 1 );
    } else if ( argc > 2 ) {
        exit ( 1 );
    }

    /*
    ** Open program file
    */
    std::fstream file( argv[ 1 ] );

    /*
    ** Current selected instruction, may not be a valid instruction, if it isn't it is counted as a comment (as is standard),
    ** if it is a valid instruction (anything that is present in the "Instruction" enum) than it is added to the program vector,
    ** which is then executed
    */
    char instruction;
    while ( file.get( instruction ) ) {

        /*
        ** Debug output
        */

        /*
        */
        std::cerr << "Reading instruction: '" << instruction << "'\n";
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
    
    file.close();

    runProgram( program );

    return 0;
}