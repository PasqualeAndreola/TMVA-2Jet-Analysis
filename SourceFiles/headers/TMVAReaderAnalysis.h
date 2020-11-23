/*!
 *  \file TMVAReaderAnalysis.h
 *  \brief Header file for \ref TMVAReaderAnalysis function.
 */

#ifndef TMVAREADERANALYSIS_H
#define TMVAREADERANALYSIS_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TPaveStats.h>
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

void TMVAReaderAnalysis(vector<TString> tmvamethods, string SBJetOutputFilename, string TMVAOutputFilename);

#endif