#include "oddcsv/oCsvTable.h"

#include "clingo/lang/func.h"
#include "clingo/type/cCharsToken.h"
#include "oddcsv/oCsvParser.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define RowSep_ 0x1E
#define CellSep_ 0x1F

bool turn_into_csv_table_o( cVarChars data,
                            oCsvTable table[static 1],
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

/*******************************************************************************

*******************************************************************************/

cChars csv_row_cell_o( oCsvRow row, int64_t col )
{
   must_be_in_range_c_( 0, col, row.cols-1 );
   int64_t count = 0;
   cChars cell;
   iterate_csv_cells_o_( itr, &cell, &row )
   {
      ++count;
      if ( count == col )
         return cell;
   }
   return (cChars)invalid_c_();
}

cChars csv_table_cell_o( oCsvTable const table[static 1],
                         int64_t row,
                         int64_t col )
{
   oCsvRow csvRow = csv_table_row_o( table, row );
   return csv_row_cell_o( csvRow, col );
}

oCsvRow csv_table_row_o( oCsvTable const table[static 1],
                         int64_t row )
{
   must_be_in_range_c_( 0, row, table->rows-1 );
   int64_t count = 0;
   oCsvRow csvRow;
   iterate_csv_rows_o_( itr, &csvRow, table )
   {
      ++count;
      if ( count == row )
         return csvRow;
   }
   return (oCsvRow){0};
}

/*******************************************************************************

*******************************************************************************/

#define finished_( Slice, Ptr )                                                \
(                                                                              \
   Ptr > end_c_( Slice ) and                                                   \
   not points_into_c_( Slice, Ptr )                                            \
)

cByte const* next_csv_entry( cBytes data,
                             cByte sep,
                             cByte const* itr,
                             cBytes dest[static 1] )
{
   if ( is_empty_c_( data ) ) return NULL;

   if ( itr == NULL )
   {
      itr = begin_c_( data );
   }

   if ( finished_( data, itr ) ) return NULL;

   cByte const* beg = itr;

   cBytes cnt = atween_c_( itr, end_c_( data ) );
   if ( is_empty_c_( cnt ) )
   {
      *dest = (cBytes)atween_c_( beg, beg );
      return beg+1;
   }

   cScanner* sca = &make_scanner_c_( cnt.s, cnt.v );
   if ( on_byte_c( sca, sep ) )
   {
      *dest = (cBytes)atween_c_( beg, beg );
      return beg+1;
   }
   if ( not move_to_byte_c( sca, sep ) )
   {
      *dest = cnt;
      itr = end_c_( cnt );
      return itr+1;
   }

   cByte const* end = sca->mem;
   *dest = (cBytes)atween_c_( beg, end );
   return end+1;
}

cByte const* next_csv_row_o( oCsvTable const table[static 1],
                             cByte const* itr,
                             oCsvRow row[static 1] )
{
   cBytes byteCell;
   itr = next_csv_entry( table->data, RowSep_, itr, &byteCell );
   row->data = byteCell;
   row->cols = table->cols;
   return itr;
}

cByte const* next_csv_cell_o( oCsvRow const row[static 1],
                             cByte const* itr,
                             cChars cell[static 1] )
{
   cBytes byteCell;
   itr = next_csv_entry( row->data, CellSep_, itr, &byteCell );
   *cell = (cChars){ .s=byteCell.s, .v=(char const*)byteCell.v };
   return itr;
}