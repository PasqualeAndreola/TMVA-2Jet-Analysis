/*!
 *  \file  test_Dataset_info.cpp
 *  \brief Unit test for \ref DatasetInfo(std::string dname, H5O_token_t dtoken, int nrows, int ncolumns) structure methods
 */

#include "headers/catch.hpp"
#include "headers/Opfunc.h"
#include "headers/TreeCreator.h"
#include "headers/Dataset_info.h"

TEST_CASE("Checking the output of the function of the structure: Dataset_info", "[Dataset_info][Output]")
{
    /* Creating a dataset info list from the h5 trial file */
    openh5("test_OpenH5_1.h5");

    /* Creating the expected output and implicitely verifyng the constructor */
    std::vector<DatasetInfo> exdataset_info_list;
    exdataset_info_list.push_back( DatasetInfo( "DS1", dataset_info_list[0].get_token(), 1, 1) );
    exdataset_info_list.push_back( DatasetInfo( "DS2", dataset_info_list[1].get_token(), 1, 1) );
    exdataset_info_list.push_back( DatasetInfo( "L1",  dataset_info_list[2].get_token(), 1, 1) );

    /* Checking the output */
    for (int i = 0; i< 3; i++)
    {
        REQUIRE(dataset_info_list[i].get_name().compare(exdataset_info_list[i].get_name()) == 0);

        /* Defining variables to get the token */
        hid_t file = H5Fopen("InputFiles/test_OpenH5_1.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
        H5O_token_t tkn = dataset_info_list[i].get_token();
        char *str;

        /* Converting the token to a string so can be tested its existence */
        REQUIRE(H5Otoken_to_str(file, &tkn, &str) >= 0 );

        REQUIRE(dataset_info_list[i].get_raw()    == exdataset_info_list[i].get_raw());

        REQUIRE(dataset_info_list[i].get_column() == exdataset_info_list[i].get_column());
    }
    
    dataset_info_list.clear();
}