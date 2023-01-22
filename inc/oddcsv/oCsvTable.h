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
   int64_t rows;
   int64_t cols;
   int64_t maxRowSize;
};
typedef struct oCsvTable oCsvTable;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDCSV_API bool turn_into_csv_table_o( cVarChars data,
                                       oCsvTable table[static 1],
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

/*******************************************************************************

*******************************************************************************/

#define iterate_csv_rows_o_( Itr, RowPtr, TablePtr )                           \
   for ( cByte const* Itr = next_csv_row_o( TablePtr, NULL, RowPtr );          \
         Itr != NULL;                                                          \
         Itr = next_csv_row_o( TablePtr, Itr, RowPtr ) )
ODDCSV_API cByte const* next_csv_row_o( oCsvTable const table[static 1],
                                       cByte const* itr,
                                       oCsvRow row[static 1] );

#define iterate_csv_cells_o_( Itr, CellPtr, RowPtr )                           \
   for ( cByte const* Itr = next_csv_cell_o( RowPtr, NULL, CellPtr );          \
         Itr != NULL;                                                          \
         Itr = next_csv_cell_o( RowPtr, Itr, CellPtr ) )
ODDCSV_API cByte const* next_csv_cell_o( oCsvRow const row[static 1],
                                         cByte const* itr,
                                         cChars cell[static 1] );

#endif