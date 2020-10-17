/*! 
 *  \file TreeJetCreator.h 
 *  \brief Header file for \ref TreeJetCreator function
 */

#ifndef TREEJETCREATOR_H
#define TREEJETCREATOR_H

#include <unistd.h>
#include <vector>
#include <iostream>
#include "OpenH5.h"
#include "Opfunc.h"
#include "Dataset_2Dread.h"
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <ClusterSequence.hh>
#include <SharedPtr.hh>
#include <PseudoJetStructureBase.hh>

int TreeJetCreator(const char *filename, double R, double pT_min);

#endif