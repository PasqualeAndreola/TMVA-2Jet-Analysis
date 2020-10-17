/*!
 * \file OpenH5.cpp
 * \brief Source file for \ref openh5 function implementation
 */

/*! \fn int openh5(const char *file_name, std::vector<std::string> names)
 *  \brief Function that finds every group of dataset, get their information and store them in a structure.
 *   
 *  It opens the \ref file_name .h5 file and analyzes it iteratively by using \ref opfunc function.\n
 *  Returns 1 if the file is opened correctly, returns 0 otherwise.
 * 
 *  \param *file_name  Name of the file that has to be opened
 */
#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"
#include "headers/Opdata.h"
#include "headers/Opfunc.h"
#include "headers/OpenH5.h"

/*Body of openh5 function, designed to open the *.h5 file and extract dataset information*/
void openh5(const char *FILE_NAME)
{
  H5O_info_t      infobuf;
  hid_t           file;
  herr_t          status;
  struct opdata   op;
  
  /*Opening file with reading properties*/
  file = H5Fopen(FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  /*File information are stored in the infobuf defined at the beginning*/
  status = H5Oget_info(file, &infobuf, H5O_INFO_ALL);

  /*Token of the dataset is assigned to one elemnt of the opdata structure*/
  op.token = infobuf.token;
  
  /*Formatting*/
  std::cout <<"/ {\n";

  /*Opfunc is iterated over the file, starting from the first group*/
  status = H5Literate (file, H5_INDEX_NAME, H5_ITER_NATIVE, NULL, opfunc, (void *) &op);

  /*Formatting*/		       
  std::cout <<"}\n";

  /*Closing the file*/
  status = H5Fclose(file);
  
}

 
