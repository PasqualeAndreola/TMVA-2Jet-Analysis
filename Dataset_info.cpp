#include "headers/Dataset_info.h"

Dataset_info::Dataset_info(std::string dname, haddr_t daddr){
    dataname = dname;
    dataaddr = daddr;
}

std::string Dataset_info::get_name(){
    return dataname;
}

haddr_t Dataset_info::get_addr(){
    return dataaddr;
}