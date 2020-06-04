/*! \file Opfunc.h
    \brief Funzione usata nella lettura iterativa di un file .h5.
    
    Questa funzione viene chiamata iterativamente nel corpo della funzione openh5().
    
    Durante lo scorrimento del file .h5, riconosce nome e posizione di ogni gruppo/dataset all'interno del file
    e lo memorizza in un buffer, che corrisponde a quello passato alla funzione openh5().
    
    Memorizza i nomi dei dataset in un vector.
    
    Ritorna una struttura che contiene lo stack degli errori riscontrati.
*/

/*! \fn herr_t opfunc (hid_t loc_id, const char *name, const H5L_info_t *info, void *operator_data, std::vector<std::string> names);
 
    \param loc_id     Identificatore del file, ottenuto dall'apertura dello stesso
    \param *name      Puntatore al nome dell'oggetto trovato
    \param *info      Struttura che contiene le informazioni raccolte
    \param *operator_data Puntatore che viene convertito in una struttura \ref opdata
    \param names      Vector che contiene i nomi dei dataset trovati
*/

#include <vector>
#include "Dataset_info.h"
#ifndef OPFUNC_H
#define OPFUNC_H

extern std::vector<Dataset_info> dataset_info_list;

herr_t opfunc (hid_t loc_id, const char *name, const H5L_info_t *info,
            void *operator_data);
            
#endif
