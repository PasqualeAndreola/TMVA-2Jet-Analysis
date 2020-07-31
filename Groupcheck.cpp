#include "headers/Opdata.h"
#include "headers/Groupcheck.h"

int groupcheck (hid_t loc_id, struct opdata *od, H5O_token_t target_token)
{
    int comparison;
    if (H5Otoken_cmp(loc_id, &od->token, &target_token, &comparison)<0)
        return 1;       /*L'indirizzo combacia*/
    else if (!od->recurs)
        return 0;       /*Raggiunto il gruppo di partenza senza casi favorevoli*/
    else
        return groupcheck (loc_id, od->prev, target_token);
                        /*Viene esaminato il nodo successivo ricorsivamente*/
}
