/*!
 *  \file  test_SBTreeJetKinematicsCreator.cpp
 *  \brief Unit test for \ref SBTreeJetKinematicsCreator(const char *filename, const char *jetfilename, int numberoffiles, unsigned long int sbjetnumber, unsigned long int eventjetnumber, double_t R, double_t pT_min) function
 */

#include "headers/catch.hpp"
#include "headers/TreeCreator.h"
#include "headers/SBTreeCreator.h"
#include "headers/SBTreeJetKinematicsCreator.h"

TEST_CASE("Checking the output of the function: SBTreeJetKinematicsCreator", "[SBTreeJetKinematicsCreator][Output]")
{
    /* We can check only the output, because the process is the same used for the other root creator function */
    TreeCreator("test_TreeCreator");
    SBTreeCreator("OutputFiles/test_TreeCreator.root", "OutputFiles/test_sbjetinput.root", 0, 0);
    SBTreeJetKinematicsCreator("OutputFiles/test_sbjetinput.root", "OutputFiles/test_sbjetout.root", 1, 10, 10, 1.0, 20);
    TFile rootfile("OutputFiles/test_sbjetout.root", "read");
    TTree *alberello1 = (TTree *)rootfile.Get("SignalJet");
    TTree *alberello2 = (TTree *)rootfile.Get("BackgroundJet");
    REQUIRE( alberello1->GetEntries() == 10);
    REQUIRE( alberello2->GetEntries() == 10);
    rootfile.Close();
}