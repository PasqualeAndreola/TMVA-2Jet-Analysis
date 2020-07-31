/*! \file OpenH5.h
    \brief Funzione che permette di aprire un file in formato .h5.
    
    Funzione utile a ricavare i nomi e le posizioni di tutti i gruppi/dataset contenuti all'interno di un dato file .h5.
    
    I nomi dei dataset vengono salvati nel vector passato come argomento.
    
    Ritorna 1 se il file è stato aperto e letto correttamente, 0 altrimenti.
*/

/*! \fn int openh5(const char *file_name, std::vector<std::string> names)
 
    \param *file_name  Nome del file h5 da aprire
    \param names   Vector dove vengono salvati i nomi dei dataset
*/

#ifndef OPENH5_H
#define OPENH5_H

void openh5 (const char *file_name);

#endif
