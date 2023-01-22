#include "oddcsv/xsv.h"

#include "clingo/lang/func.h"
#include "oddcsv/oCsvParser.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************


bool turn_into_csv_table_o( cVarChars data,
                            oXsvTable table[static 1],
                            oCsvParseCfg cfg,
                            cErrorStack es[static 1] )
{
   cRecorder* rec = &make_recorder_c_( data.s, data.v );

   oCsvParser p;
   init_csv_parser_o( &p, cfg, as_c_( cChars, data ) );

   *table = (oCsvTable){0};
   while ( not finished_csv_o( &p ) )
   {
      int64_t cols = 0;
      bool overwriteCellSep = false;
      while ( not finished_csv_row_o( &p ) )
      {
         cChars cell;
         if ( not view_raw_csv_cell_o( &p, &cell ) )
         {
            return false; // ERROR
         }
         store_raw_csv_cell_o( cell, rec );
         overwriteCellSep = record_char_c( rec, CellSep_ );
         cols++;
      }
      if ( table->cols != 0 and cols != table->cols )
      {
         return false; // ERROR rows mismatch
      }
      if ( overwriteCellSep )
      {
         move_recorder_c( rec, -1 );
         record_byte_c( rec, RowSep_ );
      }
      table->cols = cols;
      table->rows++;
   }

   table->data = recorded_bytes_c( rec );
   return true;
}
*******************************************************************************/
