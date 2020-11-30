/*!
 * \file OpenH5.cpp
 * \brief Source file for \ref openh5 function implementation
 */

/*! \fn void openh5(const char *FILE_NAME)
 *  \brief Function that finds every group of dataset, get their information and store them in a structure.
 *   
 *  It opens the \ref file_name .h5 file and analyzes it iteratively by using \ref opfunc function.\n
 *  Returns 1 if the file is opened correctly, returns 0 otherwise.
 * 
 *  \param *file_name  Name of the file that has to be opened
 */

#include "headers/OpenH5.h"

/*These namespaces can be useful*/
using namespace std;

/*Body of openh5 function, designed to open the *.h5 file and extract dataset information*/
void openh5(const char *FILE_NAME)
{

  /*Variables to adjust the print formatting and banner print*/
  vector<TString> str2beprinted;
  TString author = "P. Andreola";
  TString license = "This function is provided without warranty under the GNU GPL v3 or higher";
  str2beprinted.push_back("OpenH5");
  str2beprinted.push_back(TString::Format("Opens the input h5 file and read iteratively all groups/dataset/datatype"));
  str2beprinted.push_back(author);
  str2beprinted.push_back(license);
  PrintFuncInfo(str2beprinted);
  str2beprinted.clear();
  
  H5O_info_t      infobuf;
  hid_t           file;
  herr_t          status;
  struct opdata   op;
  
  cout << "Analyzing file: " << FILE_NAME << endl;
  cout << "It is made up of:" << endl;

  /*Opening file with reading properties*/
  file = H5Fopen(TString::Format("InputFiles/%s", FILE_NAME).Data(), H5F_ACC_RDONLY, H5P_DEFAULT);

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
  
  if (status < 0) return;
}

 
