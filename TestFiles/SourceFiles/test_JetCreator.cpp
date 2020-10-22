/*!
 *  \file  test_JetCreator.cpp
 *  \brief Unit test for \ref JetCreator(vector<PseudoJet> particles, double R, double pT_min) function
 */

#include "headers/catch.hpp"
#include "headers/JetCreator.h"
#include "headers/TreeCreator.h"
#include "headers/SBTreeCreator.h"
#include "headers/SBTreeJetKinematicsCreator.h"
#include <Error.hh>

using namespace fastjet;

TEST_CASE("Checking the general behaviour of the function: JetCreator", "[JetCreator][General]")
{
  /* Prining fastjet banner */
  ClusterSequence::print_banner();

  /* Ensuring that Jet definition has enough parameters */
  std::string error;
  try
  {
    JetDefinition(antikt_algorithm, E_scheme, Best);
  }
  catch(Error jetalgerr)
  {
    error = jetalgerr.description();
  }

  /* We require that there is an error in calling JetDefinition without sufficient parameters*/
  REQUIRE(error.compare("") != 0);
  error.clear();

  /*Testing if there are enough particles/jets */
  vector<PseudoJet> particles, jets;
  JetDefinition jet_def = JetDefinition(antikt_algorithm, 1, E_scheme, Best);
  ClusterSequence cluster_seq(particles, jet_def);
  try
  {
    jets = cluster_seq.exclusive_jets(1);
  }
  catch(Error jetalgerr)
  {
    error = jetalgerr.description();
  }

  /* We require that there is an error in selecting jets, because they are not sufficient */
  REQUIRE(error.compare("") != 0);
  error.clear();

}

TEST_CASE("Checking the output of JetCreator", "[JetCreator][Output]")
{
  /* Getting particles vector */
  openh5("test_TreeCreator.h5");
  TreeCreator("test_TreeCreator");
  SBTreeCreator("OutputFiles/test_TreeCreator.root", "OutputFiles/test_SBOut.root", 0, 1);
      
  /*Opening the *.root file containing the signal/background/event quantities*/
  TFile SBOutputroot("OutputFiles/test_SBOut.root", "read");

  /*Defining some useful variables and the structure of output trees*/
  Double_t jet1_pT, jet1_E, jet1_px, jet1_py, jet1_pz;
  Double_t jet2_pT, jet2_E, jet2_px, jet2_py, jet2_pz;

  Double_t pT, eta, phi;
  vector<PseudoJet> particles;
  vector<PseudoJet> jets;

  /*Going through alla signal/background/event trees of all files*/
  vector<TString> Tree_names;
  Tree_names.push_back("BackTrainingKinematics");
  Tree_names.push_back("SignalTrainingKinematics");
  Tree_names.push_back("EventKinematics");
  for (vector<TString>::iterator stringit = Tree_names.begin(); stringit != Tree_names.end(); ++stringit)
  {
      for (int treenumber = 1; treenumber < 2; treenumber++)
      {
        /*Getting particles' kinematic quantities*/
        TTree *Kinematics = (TTree *)SBOutputroot.Get(TString::Format("%s%d", stringit->Data(), treenumber));
        cout << endl << TString::Format("Now working on %s%d tree", stringit->Data(), treenumber) << endl;
        TBranch *pT_branch = Kinematics->GetBranch("pT");
        pT_branch->SetAddress(&pT);
        TBranch *eta_branch = Kinematics->GetBranch("eta");
        eta_branch->SetAddress(&eta);
        TBranch *phi_branch = Kinematics->GetBranch("phi");
        phi_branch->SetAddress(&phi);

        /*There are 700 particles per row*/
        unsigned long int sbjetnumber = 10, eventjetnumber = 10;
        unsigned long int jetnumber = sbjetnumber * 700;
        unsigned long int nentries = (unsigned long int)Kinematics->GetEntries();
        if (nentries != 0)
        {
          if (stringit->CompareTo("EventKinematics") == 0) jetnumber = eventjetnumber * 700;
          for (unsigned long int i = 0; i < min(jetnumber, nentries); i += 700)
          {
            for (int j = 0; j < 700; ++j)
            {
              pT_branch->GetEntry(i + j);
              eta_branch->GetEntry(i + j);
              phi_branch->GetEntry(i + j);
              particles.push_back(PseudoJet(pT * cos(phi), pT * sin(phi), pT * sinh(eta), pT * cosh(eta)));
            }

            /*Particles' vector is clustered*/
            double_t R = 1.0, pT_min = 20;
            jets = JetCreator(particles, R, pT_min);
            particles.clear();
          }
        } 
      }
  }
  /* Requires that jet are not empty*/
  REQUIRE(jets.size()!=0);

  /* Requires that there is at least an event with a pT>1.5TeV */
  REQUIRE(jets[0].pt()>1500);

  SBOutputroot.Close();
  dataset_info_list.clear();

}