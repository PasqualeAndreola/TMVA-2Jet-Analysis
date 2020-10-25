/*!
 *  \file StatusPrinter.cpp
 *  \brief Source file for \ref StatusPrinter function implementation
 */

/*!
 *  \fn void StatusPrinter(int progress) "";
 *  \brief Function used to print a banner with a progression bar
 * 
 *  This function is used to print a banner with some "[====>] x%" characters.\n
 *  They contains information about the runtime and the progress of time consuming functions.\n
 *  Global variable \c ncolumns can be defined by the user: the function will appropriately cut the progress bar.\n
 *  \param progress Completion percentage of the function being executed
 */

#include "headers/StatusPrinter.h"

//Defining color codes
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

//These namespaces can be useful
using namespace std;

//Defining a small structure to store the starting time
struct TIME
{
    chrono::steady_clock::time_point start;
    chrono::steady_clock::duration first;
};

//Global definition of number of columns of the banner
const int ncolumns = 55; /*!< Number of columns of the bar that will be printed */
struct TIME timepoint;

void StatusPrinter(int progress)
{
    if (progress == 0)
    {
        timepoint.start = chrono::steady_clock::now();
        cout << endl;
        cout << RED << "[";
        int completamento = (int)ncolumns * progress;
        for (int i = 0; i < ncolumns; ++i)
        {
            if (i < completamento)
                cout << "=";
            else if (i == completamento)
                cout << ">";
            else
                cout << " ";
        }
        cout << "]" << progress << "\r";
        cout.flush();
        cout << RESET;
    }
    else if (progress == 100)
    {
        cout << GREEN << "[";
        int completamento = (int)ncolumns * progress;
        for (int i = 0; i < ncolumns; ++i)
        {
            if (i < completamento)
                cout << "=";
            else if (i == completamento)
                cout << ">";
            else
                cout << " ";
        }
        chrono::seconds elt = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - timepoint.start);
        cout << "]100% ETA: 0[s] Elapsed time: " << elt.count() << "[s]        \r"
             << "\n\n\n";
        cout.flush();
        cout << RESET;
    }
    else
    {
        if (progress == 1)
        {
            timepoint.first = chrono::steady_clock::now() - (timepoint.start);
        }
        cout << YELLOW << "[";
        int completamento = (int)ncolumns * progress;
        for (int i = 0; i < ncolumns; ++i)
        {
            if (i < completamento)
                cout << "=";
            else if (i == completamento)
                cout << ">";
            else
                cout << " ";
        }
        chrono::seconds eta = chrono::duration_cast<chrono::seconds> (timepoint.first * (100-progress));
        chrono::seconds elt = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - timepoint.start);
        cout << "]" << progress << "% ETA: " << eta.count() << "[s] Elapsed time: " << elt.count() << "[s]\r";
        cout.flush();
        cout << RESET;
    }
}

/*!
 *  \overload StatusPrinter(std::ostream& stream, int progress) "";
 *  \brief Function used to print a banner with a progression bar
 * 
 *  This function is the overloaded version of \ref StatusPrinter(int progress).\n
 *  The user can set an ofstream to write the output to whatever he/she likes.\n
 *  The developer used this to make unit test.\n
 *  
 *  \param stream   Output where the starred banner has to be written
 *  \param progress Completion percentage of the function being executed
 */

void StatusPrinter(std::ostream &stream, int progress)
{
    if (progress == 0)
    {
        timepoint.start = chrono::steady_clock::now();
        stream << endl;
        stream << RED << "[";
        int completamento = (int)ncolumns * progress;
        for (int i = 0; i < ncolumns; ++i)
        {
            if (i < completamento)
                stream << "=";
            else if (i == completamento)
                stream << ">";
            else
                stream << " ";
        }
        stream << "]" << progress << "\r";
        stream.flush();
        stream << RESET;
    }
    else if (progress == 100)
    {
        stream << GREEN << "[";
        int completamento = (int)ncolumns * progress;
        for (int i = 0; i < ncolumns; ++i)
        {
            if (i < completamento)
                stream << "=";
            else if (i == completamento)
                stream << ">";
            else
                stream << " ";
        }
        chrono::seconds elt = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - timepoint.start);
        stream << "]100% ETA: 0[s] Elapsed time: " << elt.count() << "[s]        \r"
             << "\n\n\n";
        stream.flush();
        stream << RESET;
    }
    else
    {
        if (progress == 1)
        {
            timepoint.first = chrono::steady_clock::now() - (timepoint.start);
        }
        stream << YELLOW << "[";
        int completamento = (int)ncolumns * progress;
        for (int i = 0; i < ncolumns; ++i)
        {
            if (i < completamento)
                stream << "=";
            else if (i == completamento)
                stream << ">";
            else
                stream << " ";
        }
        chrono::seconds eta = chrono::duration_cast<chrono::seconds> (timepoint.first * (100-progress));
        chrono::seconds elt = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - timepoint.start);
        stream << "]" << progress << "% ETA: " << eta.count() << "[s] Elapsed time: " << elt.count() << "[s]\r";
        stream.flush();
        stream << RESET;
    }
}