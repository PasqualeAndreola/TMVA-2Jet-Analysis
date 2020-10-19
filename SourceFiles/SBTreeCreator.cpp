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
  /*Variables to adjust the print formatting and banner print*/
  int ncolumns2beprinted = 100;
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
  Double_t pT, eta, phi, mass, R = 1.0, pT_min = 20;
  Double_t E, px, py, pz;
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
  TBranch *pT_branch = EventKinematics.Branch("pT", &pT);
  TBranch *eta_branch = EventKinematics.Branch("eta", &eta);
  TBranch *phi_branch = EventKinematics.Branch("phi", &phi);
  TTree SignalTrainingKinematics(TString::Format("SignalTrainingKinematics%d", number), "SignalTrainingKinematics");
  TBranch *s_pT_branch = SignalTrainingKinematics.Branch("pT", &pT);
  TBranch *s_eta_branch = SignalTrainingKinematics.Branch("eta", &eta);
  TBranch *s_phi_branch = SignalTrainingKinematics.Branch("phi", &phi);
  TTree BackTrainingKinematics(TString::Format("BackTrainingKinematics%d", number), "BackTrainingKinematics");
  TBranch *b_pT_branch = BackTrainingKinematics.Branch("pT", &pT);
  TBranch *b_eta_branch = BackTrainingKinematics.Branch("eta", &eta);
  TBranch *b_phi_branch = BackTrainingKinematics.Branch("phi", &phi);

  //Reading data from the input root file
  cout << "Now distinguishing event type in the file: " << filename << endl << endl;
  unsigned long int i = 0, j = 0, flag_segnale = 1;
  for (i = 0; i < alberello->GetEntries(); i += dataset_info_list[3].get_column())
  {
    Kinematics_per_event.clear();
    block0values->GetEntry(i + dataset_info_list[3].get_column() - 1);
    flag_segnale = value;
    for (j = 0; j <= dataset_info_list[3].get_column() - 3; j += 3)
    {
      block0values->GetEntry(i + j);
      if ((flag_segnale == 0 && (dataset_info_list[3].get_column() % 3 != 0)) || sbflag == -1)
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
      else if ((flag_segnale != 0 && (dataset_info_list[3].get_column() % 3 != 0)) || sbflag == 1)
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
    if (i % (100000*dataset_info_list[3].get_column()) == 0 && i>0)
    {
      cout << i/(100000*dataset_info_list[3].get_column()) << " hundreds of thousands events have been analyzed" << endl;
    }
  }

  /*Distinguished trees are written in the output file*/
  EventKinematics.Write("", TObject::kOverwrite);
  SignalTrainingKinematics.Write("", TObject::kOverwrite);
  BackTrainingKinematics.Write("", TObject::kOverwrite);
  sbrootfile.Close();
  rootfile.Close();

  return 0;
}