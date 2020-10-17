/*!
 *  \file Groupcheck.cpp
 *  \brief Source file for \ref groupcheck function implementation
 */
#include "headers/Opdata.h"
#include "headers/Groupcheck.h"

int groupcheck(hid_t loc_id, struct opdata *od, H5O_token_t target_token)
{
    int comparison;
    if (H5Otoken_cmp(loc_id, &od->token, &target_token, &comparison) < 0)
        return 1; /*There is a loop in the data reading, because same token is opened two or more times*/
    else if (!od->recurs)
        return 0; /*There is no loop, the analysis can go on*/
    else
        return groupcheck(loc_id, od->prev, target_token);
    /*Recursive call of the groupcheck function, examining all dataset in the same group*/
}
