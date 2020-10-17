/*!
 *  \file TreeCreator.cpp
 *  \brief Source file for \ref TreeCreator function implementation
 */
/*! \fn int TreeCreator(const char * filename, const int bufferdimension) ""
 *  \brief Function that opens the *.h5 file and calls the \ref Dataset_2Dread function for every dataset stored in that particular file.
 *  
 *  This function opens a *.h5 file, then opens a token-selected dataset and begin the \ref Dataset_2Dread iteration.\n
 *  Note that there is a switch selecting the datatype which will be used as templated argument forthe function \ref Dataset_2Dread .\n
 *  It returns 0 if there is no error during the execution.
 * 
 *  \param *filename Name of the *.h5 file that has to be analyzed and name of the *.root file that will include trees filled with data read from each dataset.
 *  \param bufferdimension Dimension of the buffer that will be used to store lab of data selected from the dataspace. Choose it carefully, it depends on RAM!
 */

#include "headers/TreeCreator.h"

/*It can be useful to use these namespaces*/
using namespace std;

int TreeCreator(const char *filename, const int bufferdimension)
{

  /*Creating file*/
  string nome;
  nome.append("InputFiles/");
  nome.append(filename);
  nome.append(".h5");

  /*Opening file with reading properties*/
  hid_t file = H5Fopen(nome.data(), H5F_ACC_RDONLY, H5P_DEFAULT);
  nome.clear();
  nome.append(filename);

  /*Beginning the loop over all the dataset in the file*/
  for (int numerodataset = 0; numerodataset < dataset_info_list.size(); numerodataset++)
  {
    /*Opening the dataset using the token to extract infos*/
    hid_t dataset_id = H5Oopen_by_token(file, dataset_info_list[numerodataset].get_token());
    printf("\nWe are analyzing the dataset: %s\n", dataset_info_list[numerodataset].get_name().c_str());

    /*Evaluating datatype and allocating the correct amount of memory*/
    int classe = H5Tget_class(H5Dget_type(dataset_id));
    switch (classe)
    {
    case (0):
    {
      std::cout << "\nDataset made of integer\n";
      Dataset_2Dread<int>(dataset_id, bufferdimension, numerodataset, nome.data());
      break;
    }
    case (1):
    {
      std::cout << "\nDataset made of loat\n";
      Dataset_2Dread<double>(dataset_id, bufferdimension, numerodataset, nome.data());
      break;
    }
    case (2):
    {
      std::cout << "\nDataset made of byte\n";
      Dataset_2Dread<Byte_t>(dataset_id, bufferdimension, numerodataset, nome.data());
      break;
    }
    }
  }
  H5Fclose(file);
  return 0;
}