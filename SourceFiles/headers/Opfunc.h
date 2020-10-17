/*! 
 *  \file Opfunc.h
 *  \brief Header file for \ref opfunc function.
 */

#ifndef OPFUNC_H
#define OPFUNC_H

#include <vector>
#include "Dataset_info.h"

//It can be useful to use these namespaces
using namespace std;

extern vector<DatasetInfo> dataset_info_list;

herr_t opfunc(hid_t loc_id, const char *name, const H5L_info_t *info, void *operator_data);

#endif
