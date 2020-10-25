/*!
 *  \file SBTreeCreator.cpp
 *  \brief Source file for \ref SBTreeCreator function implementation
 */

/*! \fn int SBTreeCreator(const char *filename, const char *outputname, int sbflag, int number) "";
 *  \brief Function that create a *.root file containing signal/background/event kinematic trees
 *  
 *  This function is designed to distinguish signal from background using either the \c sbflag or other eventual event identifier.\n
 *  Returns 0 if there is no error during execution.
 * 
 *  \param *filename        Name of the *.root file that include trees to be distinguished in signal/background
 *  \param *outputname      Name of the *.root file that will contain signal, background and event trees
 *  \param sbflag           Some files contain only one kind of event. This "flag" identifies if a file is a pure signal or a pure background one
 *  \param number           Number refered to the position of the file in the list of input files that has to be analyzed
*/

#include "headers/SBTreeCreator.h"

using namespace std;

int SBTreeCreator(const char *filename, const char *outputname, int sbflag, int number)
{
  /*Defining a generic counter*/
  double counter = 0;
  int progress = 0;

  /*Variables to adjust the print formatting and banner print*/
  vector<TString> str2beprinted;
  TString author = "P. Andreola";
  TString license = "This function is provided without warranty under the GNU GPL v3 or higher";
  str2beprinted.push_back("SBTreeCreator");
  str2beprinted.push_back(TString::Format("Opens the input root file and recognize signal/background/event data"));
  str2beprinted.push_back(author);
  str2beprinted.push_back(license);
  PrintFuncInfo(str2beprinted);
  str2beprinted.clear();

  /* Defining useful variables */
  Double_t pT, eta, phi;
  Double_t value;
  vector<Double_t> Kinematics_per_event;

  /*Reading the tree of the kinematic quantities, distinguishing signal and background*/
  TFile rootfile(filename, "read");
  TTree *alberello = (TTree *)rootfile.Get(dataset_info_list[3].get_name().data());
  TBranch *block0values = alberello->GetBranch(dataset_info_list[3].get_name().data());
  block0values->SetAddress(&value);

  /*Defining trees that will store our kinematic quantities*/
  TFile sbrootfile(outputname, "update");
  TTree EventKinematics(TString::Format("EventKinematics%d", number), "EventKinematics");
  EventKinematics.Branch("pT", &pT);
  EventKinematics.Branch("eta", &eta);
  EventKinematics.Branch("phi", &phi);
  TTree SignalTrainingKinematics(TString::Format("SignalTrainingKinematics%d", number), "SignalTrainingKinematics");
  SignalTrainingKinematics.Branch("pT", &pT);
  SignalTrainingKinematics.Branch("eta", &eta);
  SignalTrainingKinematics.Branch("phi", &phi);
  TTree BackTrainingKinematics(TString::Format("BackTrainingKinematics%d", number), "BackTrainingKinematics");
  BackTrainingKinematics.Branch("pT", &pT);
  BackTrainingKinematics.Branch("eta", &eta);
  BackTrainingKinematics.Branch("phi", &phi);

  //Reading data from the input root file
  cout << "Now distinguishing event type in the file: " << filename << endl << endl;
  unsigned long int i = 0, j = 0, flag_segnale = 1;
  unsigned long int nentries = (unsigned long int) alberello->GetEntries();
  unsigned long int threenparticles = (unsigned long int) dataset_info_list[3].get_column();
  for (i = 0; i < nentries; i += threenparticles)
  {
    Kinematics_per_event.clear();
    block0values->GetEntry(i + threenparticles - 1);
    flag_segnale = value;
    for (j = 0; j <= threenparticles - 3; j += 3)
    {
      block0values->GetEntry(i + j);
      if ((flag_segnale == 0 && (threenparticles % 3 != 0)) || sbflag == -1)
      {
        pT = value;
        Kinematics_per_event.push_back(value);
        block0values->GetEntry(i + j + 1);
        eta = value;
        Kinematics_per_event.push_back(value);
        block0values->GetEntry(i + j + 2);
        phi = value;
        Kinematics_per_event.push_back(value);
        BackTrainingKinematics.Fill();
      }
      else if ((flag_segnale != 0 && (threenparticles % 3 != 0)) || sbflag == 1)
      {
        pT = value;
        Kinematics_per_event.push_back(value);
        block0values->GetEntry(i + j + 1);
        eta = value;
        Kinematics_per_event.push_back(value);
        block0values->GetEntry(i + j + 2);
        phi = value;
        Kinematics_per_event.push_back(value);
        SignalTrainingKinematics.Fill();
      }
      else
      {
        pT = value;
        Kinematics_per_event.push_back(value);
        block0values->GetEntry(i + j + 1);
        eta = value;
        Kinematics_per_event.push_back(value);
        block0values->GetEntry(i + j + 2);
        phi = value;
        Kinematics_per_event.push_back(value);
        EventKinematics.Fill();
      }
    }
    if ( (counter/(nentries-threenparticles))*100 >= progress )
    {
      StatusPrinter(progress);
      progress++;
    }
    counter= counter+threenparticles;
  }

  /*Distinguished trees are written in the output file*/
  EventKinematics.Write("", TObject::kOverwrite);
  SignalTrainingKinematics.Write("", TObject::kOverwrite);
  BackTrainingKinematics.Write("", TObject::kOverwrite);
  sbrootfile.Close();
  rootfile.Close();

  return 0;
}