/*!
 *  \file  test_OpenH5.cpp
 *  \brief Unit test for \ref openh5(const char *FILE_NAME) function
 */

#include "headers/catch.hpp"
#include "headers/OpenH5.h"

TEST_CASE("Checking the general behaviour of the function: OpenH5", "[OpenH5][General]")
{
  /* Turning off error output from hdf5 */
  H5Eset_auto(H5E_DEFAULT,NULL,NULL);

  /* The test file "test_OpenH5_0" doesn't exist: function returns -1  */
  REQUIRE(H5Fopen("InputFiles/test_OpenH5_0.h5", H5F_ACC_RDONLY, H5P_DEFAULT) == -1);

  /* The test file "test_OpenH5_1" doesn't exist: function returns a non negative address */
  REQUIRE(H5Fopen("InputFiles/test_OpenH5_1.h5", H5F_ACC_RDONLY, H5P_DEFAULT) >= 0);

  /* The info acquisition is not working: function returns a negative value */
  hid_t file;
  H5O_info_t      infobuf;
  herr_t          status;
  file = H5Fopen("InputFiles/test_OpenH5_1.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
  status = H5Oget_info(file, &infobuf, H5O_INFO_ALL);
  REQUIRE(status >= 0);

  /* The iteration has stopped abnormally, H5Literate returns a negative value */
  struct opdata   op;
  op.token = infobuf.token;
  status = H5Literate (file, H5_INDEX_NAME, H5_ITER_NATIVE, NULL, opfunc, (void *) &op);
  REQUIRE(status >= 0);

  /* File correctly closed */
  status = H5Fclose(file);
  REQUIRE(status >= 0);
}

TEST_CASE("Checking the output of OpenH5", "[OpenH5][Output]")
{
  REQUIRE( dataset_info_list[0].get_name().compare("DS1") == 0);
  REQUIRE( dataset_info_list[1].get_name().compare("DS2") == 0);
  REQUIRE( dataset_info_list[2].get_name().compare("L1") == 0);
}