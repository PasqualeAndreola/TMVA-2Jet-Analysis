/**************************************************************
 *
 * Struttura che riassume le informazioni sulla struttura del 
 * file .h5, letto ricorsivamente: è una lista di indirizzi 
 *  
 **************************************************************/

#include "H5Cpp.h"

#ifndef OPDATA_H
#define OPDATA_H

struct opdata{
  unsigned        recurs = 0;         /**< Indice ricorsivo, parte dalla radice*/
  struct opdata   *prev  = NULL;      /**< Puntatore all'iterazione precedente*/
  haddr_t         addr;               /**< Sito dove è localizzato il gruppo nel dataset*/
};

#endif
