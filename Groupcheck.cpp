#include "headers/Opdata.h"
#include "headers/Groupcheck.h"

int groupcheck (struct opdata *od, haddr_t target_addr)
{
    if (od->addr == target_addr)
        return 1;       /*L'indirizzo combacia*/
    else if (!od->recurs)
        return 0;       /*Raggiunto il gruppo di partenza senza casi favorevoli*/
    else
        return groupcheck (od->prev, target_addr);
                        /*Viene esaminato il nodo successivo ricorsivamente*/
}
