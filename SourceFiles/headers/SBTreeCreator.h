/*! \file SBTreeCreator.h
 *  \brief Header file for \ref SBTreeCreator function.
 */

#ifndef SBTREECREATOR_H
#define SBTREECREATOR_H

#include <unistd.h>
#include <iostream>
#include "OpenH5.h"
#include "Opfunc.h"
#include "Dataset_2Dread.h"

int SBTreeCreator(const char *filename, const char *outputname, int sbflag, int number);

#endif