/*! 
 *  \file JetCreator.h
 *  \brief Header file for \ref JetCreator function  
 */

#ifndef JETCREATOR_H
#define JETCREATOR_H

#include <unistd.h>
#include <vector>
#include <iostream>
#include "OpenH5.h"
#include "Opfunc.h"
#include "Dataset_2Dread.h"
#include <ClusterSequence.hh>
#include <SharedPtr.hh>
#include <PseudoJetStructureBase.hh>

//It can be useful to use these namespaces
using namespace std;
using namespace fastjet;

vector<PseudoJet> JetCreator(vector<PseudoJet> particles, double R, double pT_min);

#endif