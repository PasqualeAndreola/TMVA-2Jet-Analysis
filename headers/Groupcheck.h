/*! \file Groupcheck.h
    \brief Funzione usata per la prevenzione dei loop su un gruppo già letto.
    
    Ritorna 1 se la struttura passata alla funzione contiene l'indirizzo richiesto, 0 altrimenti.
*/

/*! \fn int groupcheck (struct opdata *od, haddr_t target_addr);
 
    \param *od     Puntatore alla struttura \ref opdata usata per memorizzare gli indirizzi dei gruppi nel file
    \param target_addr     Indirizzo appena trovato nello scorrimento del file, da confrontare con quelli memorizzati nella struttura
*/
#include "H5Cpp.h"

#ifndef GROUPCHECK_H
#define GROUPCHECK_H

int groupcheck (struct opdata *od, haddr_t target_addr);

#endif
