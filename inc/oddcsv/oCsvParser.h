#ifndef ODDCSV_OCSVPARSER_H
#define ODDCSV_OCSVPARSER_H

#include "clingo/io/cScanner.h"
#include "oddcsv/apidecl.h"
#include "oddcsv/oCsvCell.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvParser
{
   cRune sep;
   cScanner sca;
   char const* err;
};
typedef struct oCsvParser oCsvParser;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDCSV_API bool init_csv_parser_o( oCsvParser p[static 1], cChars full );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API bool next_csv_cell_o( oCsvParser p[static 1],
                                 oCsvCell cell[static 1] );

#endif