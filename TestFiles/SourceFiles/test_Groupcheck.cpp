/*!
 *  \file  test_Groupcheck.cpp
 *  \brief Unit test for \ref groupcheck(hid_t loc_id, struct opdata *od, H5O_token_t target_token) structure methods
 */

#include "headers/catch.hpp"
#include "headers/Groupcheck.h"
#include "headers/OpenH5.h"

TEST_CASE("Checking the general behaviour of the function: Groupcheck", "[Groupcheck][General]")
{
    /* Creating a dataset info list from the h5 trial file to test Groupcheck function implementation*/
    openh5("test_OpenH5_1.h5");
    hid_t file = H5Fopen("InputFiles/test_OpenH5_1.h5", H5F_ACC_RDONLY, H5P_DEFAULT);    
    H5O_token_t tkn1 = dataset_info_list[0].get_token();
    H5O_token_t tkn2 = dataset_info_list[1].get_token();
    int cmp;

    /* Requiring that comparison is executed correctly*/
    REQUIRE( H5Otoken_cmp(file, &tkn1, &tkn2, &cmp) >= 0);    

    /* Comparing two different tokens to force H5Otoken_cmp to return a non 0 value */
    REQUIRE( cmp != 0);

    /* Comparing two same tokens to force H5Otoken_cmp to return a 0 value */
    REQUIRE( H5Otoken_cmp(file, &tkn1, &tkn1, &cmp) >= 0); 
    REQUIRE( cmp == 0);   
}

TEST_CASE("Checking the output of the function: Groupcheck", "[Groupcheck][General]")
{
    hid_t file = H5Fopen("InputFiles/test_OpenH5_1.h5", H5F_ACC_RDONLY, H5P_DEFAULT);    
    H5O_token_t tkn1 = dataset_info_list[0].get_token();
    H5O_token_t tkn2 = dataset_info_list[1].get_token();
    struct opdata *op = new struct opdata[2];
    op[1].recurs = op[0].recurs+1;
    op[1].token = tkn1;
    op[1].prev = op;
    op[0].recurs = 0;
    op[0].token = tkn1;
    op[0].prev = NULL;
    
    /* Requiring that there is the same token in the opdata structure*/
    REQUIRE(groupcheck(file, op, tkn1) > 0);

    /* Requiring that there is not the same token in the opdata structure*/
    REQUIRE(groupcheck(file, op, tkn2) <= 0);
}