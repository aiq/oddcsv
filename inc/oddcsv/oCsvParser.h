#ifndef ODDCSV_OCSVPARSER_H
#define ODDCSV_OCSVPARSER_H

#include "clingo/io/cScanner.h"
#include "clingo/string/CStringList.h"
#include "oddcsv/apidecl.h"
#include "oddcsv/misc.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvParser
{
   oCsvParseCfg cfg;
   cScanner sca;
   char const* err;
};
typedef struct oCsvParser oCsvParser;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDCSV_API bool init_csv_parser_o( oCsvParser p[static 1],
                                   oCsvParseCfg cfg,
                                   cChars full );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API bool finished_csv_o( oCsvParser p[static 1] );

ODDCSV_API bool move_to_next_csv_row_o( oCsvParser p[static 1] );

ODDCSV_API bool in_csv_row_o( oCsvParser p[static 1] );

ODDCSV_API bool view_raw_csv_cell_o( oCsvParser p[static 1],
                                     cChars cell[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API bool parse_csv_string_row_o( oCsvParser p[static 1],
                                        CStringList* row );

#endif