/*! \file SBTreeJetKinematicsCreator.h
 *  \brief Header file for \ref SBTreeJetKinematicsCreator function.
 */

#ifndef SBTREEJETKINEMATICSCREATOR_H
#define SBTREEJETKINEMATICSCREATOR_H

#include <unistd.h>
#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TString.h>
#include <ClusterSequence.hh>
#include <SharedPtr.hh>
#include <PseudoJetStructureBase.hh>
#include "JetCreator.h"
#include "PrintFuncInfo.h"

int SBTreeJetKinematicsCreator(const char *filename, const char *jetfilename, int numberoffiles, unsigned long int sbjetnumber, unsigned long int eventjetnumber, double_t R, double_t pT_min);

#endif