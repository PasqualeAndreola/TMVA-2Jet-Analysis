#include "headers/Dataset_info.h"

Dataset_info::Dataset_info(std::string dname, H5O_token_t dtoken, int nrighe, int ncolonne){
    dataname = dname;
    datatoken = dtoken;
    numerorighe = nrighe;
    numerocolonne = ncolonne;
}

std::string Dataset_info::get_name(){
    return dataname;
}

H5O_token_t Dataset_info::get_token(){
    return datatoken;
}

int Dataset_info::get_raw(){
    return numerorighe;
}

int Dataset_info::get_column(){
    return numerocolonne;
}