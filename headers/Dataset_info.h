/************************************************
 *
 * Struttura che contiene indirizzo e nome di un dataset
 *
 *************************************************/

#include "H5Cpp.h"

#ifndef DATASET_INFO_H
#define DATASET_INFO_H

class Dataset_info{
    private:
        std::string dataname;
        haddr_t dataaddr;
    public:
        Dataset_info(std::string dataname, haddr_t dataaddr);
        std::string get_name();
        haddr_t get_addr();
};

#endif