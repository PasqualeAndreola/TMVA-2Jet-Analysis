#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"
#include "headers/Opdata.h"
#include "headers/Opfunc.h"
#include "headers/OpenH5.h"

/*Corpo della funzione OpenH5, atta ad aprire il file .h5 ed estrarne la struttura*/
int openh5(const char *FILE_NAME)
{
  H5O_info_t      infobuf;
  hid_t           file;
  herr_t          status;
  struct opdata   op;
  
  /*Viene aperto il file in lettura*/
  file = H5Fopen(FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  /*Vengono scaricate le informazioni del file nel buffer "infobuf" definito all'inizio del main*/
  status = H5Oget_info(file, &infobuf);

  /*Si inizializza il sito di partenza dell'iterazione*/
  op.addr = infobuf.addr;
  
  /*Stampo qualcosa*/
  std::cout <<"/ {\n";

  /*Si usa la funzione di iterazione sui gruppi in un file .h5, partendo dalla radice*/
  status = H5Literate (file, H5_INDEX_NAME, H5_ITER_NATIVE, NULL, opfunc, (void *) &op);

  /*Stampo il qualcosa opposto*/		       
  std::cout <<"}\n";

  /*Chiudo il file*/
  status = H5Fclose(file);
  
}

 
