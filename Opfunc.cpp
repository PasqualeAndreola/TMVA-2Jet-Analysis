#include "headers/Opdata.h"
#include "headers/Groupcheck.h"
#include "headers/Opfunc.h"
#include <string>
#include <vector>

std::vector<Dataset_info> dataset_info_list;

/*Corpo della funzione che cerca, ottiene e stampa i nomi di ogni struttura nel file .h5*/
herr_t opfunc (hid_t loc_id, const char *name, const H5L_info_t *info,
	       void *operator_data)
{
    hid_t dataset_id , dataspace_id;
    hsize_t dims_out[2] = {1, 1};
    herr_t          status, return_val = 0;
    H5O_info_t      infobuf;
    struct opdata   *od = (struct opdata *) operator_data; /*Conversione di tipo*/
    unsigned        spaces = 2*((od->recurs)+1);             /*Numero di spazi bianchi da lasciare*/

    /*
     * Viene riconosciuto il tipo di oggetto ed il suo nome.
     * Il nome viene passato al puntatore argomento della funzione.
     */
    status = H5Oget_info_by_name(loc_id, name, &infobuf, H5O_INFO_ALL,H5P_DEFAULT);
    printf ("%*s", spaces, "");     /*Formattazione della stampa*/
    switch (infobuf.type) {
        case H5O_TYPE_GROUP:
            printf ("Group: %s {\n", name);

            /*
             * Si controlla l'indirizzo del gruppo collegato alla struttura.
             * Il controllo viene effettuato comunque, perché il counter 
             * non è affidabile in presenza di eventuali collegamenti simbolici.
             */
            if ( groupcheck (loc_id, od, infobuf.token) ) {
                printf ("%*s  Warning: Loop detected!\n", spaces, "");
            }
            else {

                /*
                 * Inizializza un nuovo data structure e comincia l'iterazione.
                 * La nuova data structure ha un puntatore alla vecchia 
                 */
                struct opdata nextod;
                nextod.recurs = (od->recurs) + 1;
                nextod.prev = od;
                nextod.token = infobuf.token;
                return_val = H5Literate_by_name (loc_id, name, H5_INDEX_NAME,
                            H5_ITER_NATIVE, NULL, opfunc, (void *) &nextod,
                            H5P_DEFAULT);
            }
            printf ("%*s}\n", spaces, "");
            break;
        case H5O_TYPE_DATASET:
            dataset_id = H5Oopen_by_token(loc_id, infobuf.token);
            dataspace_id = H5Dget_space(dataset_id);
            H5Sget_simple_extent_dims(dataspace_id,dims_out,NULL);
            dataset_info_list.push_back(Dataset_info(std::string(name), infobuf.token, dims_out[0], dims_out[1]));
            printf ("Dataset: %s\n", name);
            break;
        case H5O_TYPE_NAMED_DATATYPE:
            printf ("Datatype: %s\n", name);
            break;
        default:
            printf ( "Unknown: %s\n", name);
    }
    return return_val;
}
 
