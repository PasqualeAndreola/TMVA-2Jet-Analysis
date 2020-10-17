/*! \file Dataset_info.h
 *
 * \brief Header file for \ref DatasetInfo structure definition
 *
 * \link DatasetInfo \endlink stores information about dataset name, token (needed to locate the file) and dimensions.
 */

/*!
 * \class DatasetInfo Dataset_info.h
 * 
 * \brief Class needed to identify a dataset for our purpose
 * 
 */

#ifndef DATASET_INFO_H
#define DATASET_INFO_H

#include "H5Cpp.h"

//It can be useful to use these namespaces
using namespace std;

class DatasetInfo
{
private:
    string dataname;       /*!< String that stores the dataset name */
    H5O_token_t datatoken; /*!< Structure that holds the dataset token, needed to identify dataset location in the memory once the *.h5 file is opened*/
    int rownumber;         /*!< Number of rows of the dataset */
    int columnnumber;      /*!< Number of columns of the dataset */
public:

/*!
 *
 * Standard constructor for \link DatasetInfo \endlink structure.\n
 * \link dataname \endlink is the string which represents the dataset name.\n
 * \link datatoken \endlink is the token obtained from the \link opdata \endlink structure.\n
 * \link rownumber \endlink and \link columnnumber \endlink are needed to create smart buffer while reading the dataset.
 *
 */

    DatasetInfo(string dataname, H5O_token_t datatoken, int rownumber, int columnnumber);

    string get_name(); /*!< Function that returns the string \link dataname \endlink which is stored as a private member */

    H5O_token_t get_token(); /*!< Function that returns the H5O token structure \link datatoken \endlink which is stored as a private member*/

    int get_raw(); /*!< Function that returns the int \link rownumber \endlink which is stored as a private member*/

    int get_column(); /*!< Function that returns the int \link columnnumber \endlink which is stored as a private member*/
};

#endif