/*! \file Dataset_info.cpp
 *  \brief Source file for \ref DatasetInfo members implementation
 */

#include "headers/Dataset_info.h"

DatasetInfo::DatasetInfo(std::string dname, H5O_token_t dtoken, int nrows, int ncolumns)
{
    dataname = dname;
    datatoken = dtoken;
    rownumber = nrows;
    columnnumber = ncolumns;
}

std::string DatasetInfo::get_name()
{
    return dataname;
}

H5O_token_t DatasetInfo::get_token()
{
    return datatoken;
}

int DatasetInfo::get_raw()
{
    return rownumber;
}

int DatasetInfo::get_column()
{
    return columnnumber;
}