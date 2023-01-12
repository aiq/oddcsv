#include "oddcsv/oCsvTable.h"

#include "oddcsv/oCsvParser.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool turn_into_csv_table_o( cVarChars data,
                            oCsvTable table[static 1],
                            oCsvParseCfg cfg,
                            cErrorStack es[static 1] )
{
   cRecorder* rec = &make_recorder_c_( data.s, data.v );

   oCsvParser p;
   init_csv_parser_o( &p, cfg, as_c_( cChars, data ) );

   *table = (oCsvTable){0};
   bool first = true;
   while ( not finished_csv_o( &p ) )
   {
      int64_t cols = 0;;
      while ( in_csv_row_o( &p ) )
      {
         if ( not first )
         {
            record_char_c( rec, '\0' );
         }
         cChars cell;
         if ( not view_raw_csv_cell_o( &p, &cell ) )
         {
            return false; // ERROR
         }
         store_raw_csv_cell_o( cell, rec );
         cols++;
         first = false;
      }
      if ( table->cols != 0 and cols != table->cols )
      {
         return false; // ERROR rows mismatch
      }
      table->cols = cols;
      table->rows++;
   }

   table->data = recorded_bytes_c( rec );
   return true;
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