/*!
 *  \file  test_Opfunc.cpp
 *  \brief Unit test for \ref opfunc(hid_t loc_id, const char *name, const H5L_info_t *info, void *operator_data) function
 */

#include "headers/catch.hpp"
#include "headers/Opfunc.h"
#include "headers/TreeCreator.h"
#include "headers/Opfunc.h"

TEST_CASE("Checking the general behaviour of the function: Opfunc", "[Opfunc][General]")
{
    hid_t loc_id;
    H5O_info_t infobuf;
    loc_id = H5Fopen("InputFiles/test_OpenH5_1.h5",  H5F_ACC_RDONLY, H5P_DEFAULT);

    /* Requiring that info are gotten correctly*/
    REQUIRE(H5Oget_info_by_name(loc_id, "DS1", &infobuf, H5O_INFO_ALL, H5P_DEFAULT) >= 0);

    /* Requiring that token are correctly opened by the H5 method */
    hid_t dataset_id = H5Oopen_by_token(loc_id, infobuf.token);
    REQUIRE(dataset_id != H5I_INVALID_HID);

    /* Requiring that dataspace is correctly read */
    hid_t dataspace_id = H5Dget_space(dataset_id);
    REQUIRE(dataspace_id >= 0);

    /* Requiring the correct acquisition of dimensions */
    hsize_t dims_out[2] = {100, 1};
    REQUIRE(H5Sget_simple_extent_dims(dataspace_id, dims_out, NULL)>=0);
    REQUIRE(dims_out[0]==1); //It's important because we have set it to 100 during dims_out definition
    REQUIRE(dims_out[1]==1);
}

TEST_CASE("Checking the output of the function: Opfunc", "[Opfunc][Output]")
{
    hid_t loc_id;
    H5O_info2_t infobuf;
    H5Oget_info_by_name(loc_id, "DS2", &infobuf, H5O_INFO_ALL, H5P_DEFAULT);
    struct opdata op;
    op.token = infobuf.token;
    loc_id = H5Fopen("InputFiles/test_OpenH5_1.h5",  H5F_ACC_RDONLY, H5P_DEFAULT);
    H5L_info_t *linfo;

    /* Requiring that we can extract correctly information about iterator link from a group*/
    REQUIRE( H5Lget_info(loc_id, "G1", linfo, H5P_DEFAULT) >= 0);

    /* Requiring that we can correctly use opfunc over the entire group */
    REQUIRE( opfunc(loc_id, "G1", linfo, (void *) &op) >= 0);

    /* Requiring that dataset name is correctly stored in the dataset_info_list */
    REQUIRE( dataset_info_list[0].get_name().compare("DS2") == 0);
    dataset_info_list.clear();
}