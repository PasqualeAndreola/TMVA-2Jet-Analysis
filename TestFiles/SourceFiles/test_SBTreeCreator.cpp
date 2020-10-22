/*!
 *  \file  test_SBTreeCreator.cpp
 *  \brief Unit test for \ref SBTreeCreator(const char *filename, const char *outputname, int sbflag, int number) function
 */

#include "headers/catch.hpp"
#include "headers/SBTreeCreator.h"

TEST_CASE("Checking the general behaviour of the function: SBTreeCreator", "[SBTreeCreator][General]")
{
    /* We require that the function returns a positive value to ensure that there are no errors */
    REQUIRE(SBTreeCreator("OutputFiles/test_TreeCreator.root", "OutputFiles/test_SBOutput.root", 0, 1)>=0);

    /* Requiring that the file exists and is opened correctly*/
    string err;
    TFile rootfile("OutputFiles/test_TreeCreator.root", "read");
    if (rootfile.IsZombie())
    {
        err = "File non esistente";
    }
    REQUIRE(err.compare("File non esistente") != 0);

    /* Checking the number of entries */
    TTree *alberello = (TTree *)rootfile.Get("block0_values");
    REQUIRE( alberello->GetEntries() == 2101000);

    /* Checking that branch is active */
    REQUIRE( alberello->GetBranchStatus("block0_values") == 1);
    TBranch *block0values = alberello->GetBranch("block0_values");
    double_t value;
    block0values->SetAddress(&value);

    /* Creating a small tree with the same function procedure */
    TFile sbrootfile("OutputFiles/test_sbout.root", "recreate");
    double_t pT, eta, phi;
    vector<Double_t> Kinematics_per_event;
    int flag_segnale = 1;
    TTree SignalTrainingKinematics("SignalTrainingKinematics", "SignalTrainingKinematics");
    SignalTrainingKinematics.Branch("pT", &pT);
    SignalTrainingKinematics.Branch("eta", &eta);
    SignalTrainingKinematics.Branch("phi", &phi);
    for (int i = 0; i < 2101*1000; i += 2101)
    {
        Kinematics_per_event.clear();
        block0values->GetEntry(i + 2101 - 1);
        int flag_segnale = value;
        for (int j = 0; j <= 2101 - 3; j += 3)
        {
            block0values->GetEntry(i + j);
            if ((flag_segnale != 0 && (2101 % 3 != 0)))
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
        }
    }
    SignalTrainingKinematics.Write("", TObject::kOverwrite);
    sbrootfile.Close();

    /* Checking that the tree is correctly written */
    TFile sbout("OutputFiles/test_sbout.root","read");
    TTree *checker = (TTree *)sbout.Get("SignalTrainingKinematics");
    REQUIRE( checker->GetEntries() == 65100);
    rootfile.Close();
    sbout.Close();
}

TEST_CASE("Checking the output of the function: SBTreeCreator", "[SBTreeCreator][Output]")
{
    TFile rootfile("OutputFiles/test_SBOutput.root", "read");
    TTree *alberello1 = (TTree *)rootfile.Get("SignalTrainingKinematics1");
    TTree *alberello2 = (TTree *)rootfile.Get("BackTrainingKinematics1");
    TTree *alberello3 = (TTree *)rootfile.Get("EventKinematics1");
    REQUIRE( alberello1->GetEntries() == 65100);
    REQUIRE( alberello2->GetEntries() == 634900);
    REQUIRE( alberello3->GetEntries() == 0);
    rootfile.Close();
}