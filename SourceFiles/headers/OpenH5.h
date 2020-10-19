/*! \file OpenH5.h
 *   \brief Header file for \ref openh5 function.
 */

#ifndef OPENH5_H
#define OPENH5_H

#include <TString.h>
#include "PrintFuncInfo.h"
#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"
#include "Opdata.h"
#include "Opfunc.h"

void openh5(const char *file_name);

#endif
