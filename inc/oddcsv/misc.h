#ifndef ODDCSV_CONFIG_H
#define ODDCSV_CONFIG_H

#include "clingo/io/cRecorder.h"
#include "clingo/type/cRune.h"
#include "oddcsv/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvBuildCfg
{
   cRune sep;
   bool useCRLF;
   bool quoteSpace;
};
typedef struct oCsvBuildCfg oCsvBuildCfg;

struct oCsvParseCfg
{
   cRune sep;
   cRune comment;
   bool trim;
};
typedef struct oCsvParseCfg oCsvParseCfg;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define iterate_csv_cell_o_( Itr, Rune, Cell )                                 \
   for ( char const* Itr = next_csv_cell_rune_o( Cell, NULL, &Rune );          \
         Itr != NULL;                                                          \
         Itr = next_csv_cell_rune_o( Cell, Itr, &Rune ) )

char const* next_csv_cell_rune_o( cChars cell,
                                  char const* itr,
                                  cRune r[static 1] );

ODDCSV_API bool store_raw_csv_cell_o( cChars cell, cRecorder rec[static 1] );

#endif