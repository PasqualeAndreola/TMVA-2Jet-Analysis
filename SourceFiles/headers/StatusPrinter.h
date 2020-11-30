/*! \file StatusPrinter.h
 *  \brief Header file for \link StatusPrinter \endlink function.
 */

#ifndef STATUS_PRINTER_H
#define STATUS_PRINTER_H

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <TString.h>

/*These namespaces can be useful*/
using namespace std;

void StatusPrinter(int progress);
void StatusPrinter(std::ostream& stream, int progress);

#endif