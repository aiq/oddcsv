#include "oddcsv/oCsvTable.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool make_csv_table_o( oCsvTable table[static 1],
                       cVarChars data,
                       oCsvParseCfg cfg,
                       cErrorStack es[static 1] )
{
   return false;
}

/*******************************************************************************

*******************************************************************************/

cChars csv_row_cell_o( oCsvRow row, int64_t col )
{
   return c_c( "" );
}

cChars csv_table_cell_o( oCsvTable const table[static 1],
                         int64_t row,
                         int64_t col )
{
   return c_c( "" );
}

oCsvRow csv_table_row_o( oCsvTable const table[static 1],
                         int64_t row )
{
   return (oCsvRow){0};
}