#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;
using std:: exception;
#include "Auxiliaries.h"


namespace mtm
{
    class Exception: public std::exception
    {

    };
    class IllegalArgument: public Exception
    {
        public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell: public Exception
    {
         public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: IllegalCell";
        }
    };
    class CellEmpty: public Exception
    {
         public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: CellEmpty";
        }
    };
    class MoveTooFar: public Exception
    {
         public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: MoveTooFar";
        }
    };
    class CellOccupied: public Exception
    {
         public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: CellOccupied";
        }
    };
    class  OutOfRange: public Exception
    {
         public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: OutOfRange";
        }
    };
    class OutOfAmmo: public Exception
    {
         public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: OutOfAmmo";
        }
    };
    class IllegalTarget: public Exception
    {
         public: 
        const char* what() noexcept
        {
            return "A game related error has occurred: IllegalTarget";
        }
    };
}

#endif