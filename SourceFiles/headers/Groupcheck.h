/*! 
 *  \file Groupcheck.h
 *  \brief Header file for \ref groupcheck function
 */

/*! \fn int groupcheck(hid_t loc_id, struct opdata *od, H5O_token_t target_token) Groupchceck.h
 *  
 *  \brief Function that controls possible loop in dataset reading
 *  
 *  HD5 dataset are often stored in groups: this function is needed to check that no dataset is read more than one time.\n
 *  \link groupcheck \endlink returns 1 if the iterator goes through the same dataset two or more times. Returns 0 otherwise.
 * 
 *  \param loc_id Location identifier of the dataset stored in memory
 * 
 *  \param od     Pointer to the struct \ref opdata used to store the information about group structure and its dataset organization
 *  
 *  \param target_token Token of the currently opened dataset. It will be compared to other tokens stored in \ref opdata
 *  
*/

#ifndef GROUPCHECK_H
#define GROUPCHECK_H

#include "H5Cpp.h"

int groupcheck(hid_t loc_id, struct opdata *od, H5O_token_t target_token);

#endif
