/*!
 * \file Opfunc.cpp
 * \brief Source file for \ref opfunc function implementation
 */

/*! \fn herr_t opfunc (hid_t loc_id, const char *name, const H5L_info_t *info, void *operator_data);
 *  \brief This is the function used as an iterative operator called by \ref openh5 function.
 * 
 *  While going through a *.h5 file, this function identifies info about every group/dataset/datatype, storing them in a list.\n
 *  Returns a structure holding the error stack: it can be read using some \c HDF5 function. Refer to its documentation
 * 
 *  \param loc_id     *.h5 file location identifier, obtained from \ref openh5 function
 *  \param *name      Pointer to the name of the *.h5 file
 *  \param *info      Structure that holds info about the group/dataset/datatype read from the iteration
 *  \param *operator_data Pointer to \ref opdata structure, that will hold tokens of all the dataset in the file
*/

#include "headers/Opdata.h"
#include "headers/Groupcheck.h"
#include "headers/Opfunc.h"
#include <string>
#include <vector>

//It can be useful to use these namespaces
using namespace std;

//Importing the dataset info list variable
vector<DatasetInfo> dataset_info_list;

/*This function is designed to get all the useful information about every dataset in the *.h5 file */
herr_t opfunc(hid_t loc_id, const char *name, const H5L_info_t *info,
              void *operator_data)
{
    hid_t dataset_id, dataspace_id;
    hsize_t dims_out[2] = {1, 1};
    herr_t status, return_val = 0;
    H5O_info_t infobuf;
    struct opdata *od = (struct opdata *)operator_data; /*Type casting*/
    unsigned spaces = 2 * ((od->recurs) + 1);           /*Number of space to correctly format the text output*/

    /*
     * The H5O gets info about the structure by the name and the (relative) location in the file.
     * Name is passed to this function as a index from the call of the H5Literate function in OpenH5.cpp.
     */
    status = H5Oget_info_by_name(loc_id, name, &infobuf, H5O_INFO_ALL, H5P_DEFAULT);
    printf("%*s", spaces, ""); /*Text formatting*/
    switch (infobuf.type)
    {
    case H5O_TYPE_GROUP:
        printf("Group: %s {\n", name);

        /*
         * Groupcheck is called to ensure the absence of loop over various iterations.
         */
        if (groupcheck(loc_id, od, infobuf.token))
        {
            printf("%*s  Warning: Loop detected!\n", spaces, "");
        }
        else
        {

            /*
             * The opdata structure is updated with the new token, that is confirmed to be loop-safe
             */
            struct opdata nextod;
            nextod.recurs = (od->recurs) + 1;
            nextod.prev = od;
            nextod.token = infobuf.token;

            /*Recursive call to the iterator, to examine all dataset included into a group*/
            return_val = H5Literate_by_name(loc_id, name, H5_INDEX_NAME,
                                            H5_ITER_NATIVE, NULL, opfunc, (void *)&nextod,
                                            H5P_DEFAULT);
        }
        printf("%*s}\n", spaces, "");
        break;

    case H5O_TYPE_DATASET:
        /*If a dataset is detected, infos about datatype, dataspace and dataset dimensions are extracted*/
        dataset_id = H5Oopen_by_token(loc_id, infobuf.token);
        dataspace_id = H5Dget_space(dataset_id);
        H5Sget_simple_extent_dims(dataspace_id, dims_out, NULL);

        /*Information about dataset are stored into a datasetinfo list*/
        dataset_info_list.push_back(DatasetInfo(string(name), infobuf.token, dims_out[0], dims_out[1]));
        printf("Dataset: %s\n", name);
        break;

    case H5O_TYPE_NAMED_DATATYPE:
        printf("Datatype: %s\n", name);
        break;

    default:
        printf("Unknown: %s\n", name);
    }
    return return_val;
}
