/*! \file Opdata.h
 *
 *  \brief Header file for \ref opdata structure definition
 */

/*! \struct opdata
 *
 *  \brief Recursive structure used to store every token referred to all group's dataset   
 * 
 */

#include "H5Cpp.h"

#ifndef OPDATA_H
#define OPDATA_H

struct opdata
{
  unsigned recurs = 0;        /*!< Recursive index of the structure*/
  struct opdata *prev = NULL; /*!< Pointer to the previous \ref opdata structure*/
  H5O_token_t token;          /*!< Token referred to a specific dataset*/
};

#endif
