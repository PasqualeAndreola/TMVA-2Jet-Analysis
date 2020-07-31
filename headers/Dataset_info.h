/************************************************
 *
 * Struttura che contiene nome, token e dimensioni di un dataset
 *
 *************************************************/

#include "H5Cpp.h"

#ifndef DATASET_INFO_H
#define DATASET_INFO_H

class Dataset_info{
    private:
        std::string dataname;
        H5O_token_t datatoken;
        int numerorighe, numerocolonne;
    public:
        Dataset_info(std::string dataname, H5O_token_t datatoken, int numerorighe, int numerocolonne);
        std::string get_name();
        H5O_token_t get_token();
        int get_raw();
        int get_column();
};

#endif