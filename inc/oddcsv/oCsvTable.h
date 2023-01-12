#ifndef ODDCSV_OCSVTABLE_H
#define ODDCSV_OCSVTABLE_H

#include "clingo/lang/error.h"
#include "clingo/type/cBytes.h"
#include "clingo/type/cChars.h"
#include "oddcsv/apidecl.h"
#include "oddcsv/misc.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvRow
{
   cBytes data;
   int64_t cols;
};
typedef struct oCsvRow oCsvRow;

struct oCsvTable
{
   cBytes data;
   int64_t maxRowSize;
   int64_t rows;
   int64_t cols;
};
typedef struct oCsvTable oCsvTable;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDCSV_API bool make_csv_table_o( oCsvTable table[static 1],
                                  cVarChars data,
                                  oCsvParseCfg cfg,
                                  cErrorStack es[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API cChars csv_row_cell_o( oCsvRow row, int64_t col );

ODDCSV_API cChars csv_table_cell_o( oCsvTable const table[static 1],
                                    int64_t row,
                                    int64_t col );

ODDCSV_API oCsvRow csv_table_row_o( oCsvTable const table[static 1],
                                    int64_t row );

#endif