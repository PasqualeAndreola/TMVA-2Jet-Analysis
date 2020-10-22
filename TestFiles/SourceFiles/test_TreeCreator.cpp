/*!
 *  \file  test_TreeCreator.cpp
 *  \brief Unit test for \ref SBTreeJetKinematicsCreator(const char *filename, const char *jetfilename, int numberoffiles, unsigned long int sbjetnumber, unsigned long int eventjetnumber, double_t R, double_t pT_min) function
 */

#include "headers/catch.hpp"
#include "headers/TreeCreator.h"

TEST_CASE("Checking the general behaviour of the function: TreeCreator", "[TreeCreator][General]")
{
    /*Opening file with reading properties (opening has been already tested) */
    dataset_info_list.clear();
    openh5("test_TreeCreator.h5");
    hid_t file = H5Fopen("InputFiles/test_TreeCreator.h5", H5F_ACC_RDONLY, H5P_DEFAULT);

    /* Checking the correctness of data typing recognition*/
    hid_t dataset_id1 = H5Oopen_by_token(file, dataset_info_list[0].get_token());
    int classe1 = H5Tget_class(H5Dget_type(dataset_id1));
    REQUIRE(classe1 == 0);

    hid_t dataset_id3 = H5Oopen_by_token(file, dataset_info_list[3].get_token());
    int classe3 = H5Tget_class(H5Dget_type(dataset_id3));
    REQUIRE(classe3 == 1);
    dataset_info_list.clear();
}

TEST_CASE("Checking the output of the function: TreeCreator", "[TreeCreator][Output]")
{
    /* Check the output means to test root tree creator function */
    TreeCreator("test_TreeCreator");
    TFile rootfile("OutputFiles/test_TreeCreator.root", "read");
    TTree *alberello1 = (TTree *)rootfile.Get("axis0");
    TTree *alberello2 = (TTree *)rootfile.Get("axis1");
    TTree *alberello3 = (TTree *)rootfile.Get("block0_items");
    TTree *alberello4 = (TTree *)rootfile.Get("block0_values");
    REQUIRE( alberello1->GetEntries() == 2101);
    REQUIRE( alberello2->GetEntries() == 1000);
    REQUIRE( alberello3->GetEntries() == 2101);
    REQUIRE( alberello4->GetEntries() == 2101000);
    rootfile.Close();
}