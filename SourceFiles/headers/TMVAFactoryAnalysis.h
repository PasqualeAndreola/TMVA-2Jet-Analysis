/*!
 *  \file TMVAFactoryAnalysis.h
 *  \brief Header file for \ref TMVAFactoryAnalysis function.
 */

#ifndef TMVAFACTORYANALYSIS_H
#define TMVAFACTORYANALYSIS_H

#include <iostream>
#include <vector>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <THStack.h>
#include <TLegend.h>
#include <TMVA/Factory.h>
#include <TMVA/Reader.h>
#include <TMVA/TMVAGui.h>
#include <TMVA/DataLoader.h>
#include <TMVA/Tools.h>
#include <TString.h>

/*These namespaces can be useful*/
using namespace std;

void TMVAFactoryAnalysis(vector<TString> tmvamethods, vector<long unsigned int> nevents, string SBJetOutputFilename, string TMVAOutputFilename);

#endif