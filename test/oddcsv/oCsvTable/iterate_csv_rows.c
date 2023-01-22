#include "clingo/lang/expect.h"
#include "oddcsv/oCsvTable.h"

#include "clingo/io/print.h"

TEMP_SLICE_C_(
   test,
   {
      char const* csv;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

void println_bytes( char const name[static 1], cBytes bytes )
{
   print_c_( "{s}", name );
   for_each_c_( cByte const*, b, bytes )
   {
      if ( *b >= 0x20 )
         print_c_( "{c}", *b );
      else
         print_c_( "[{b:x}]", *b );
   }
   println_c_( "" );
}

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "a;b;c\n;d;\ne;f;", "a-b-c-|-d--|e-f--|" )
   );

   for_each_c_( test const*, t, tests )
   {
      cVarChars csvData = var_chars_c_( 512 );
      csvData.s = set_chars_c_( csvData, t->csv );

      cErrorStack* es = &error_stack_c_( 256 );
      oCsvParseCfg cfg = { .sep=rune_c( ";" ) };
      oCsvTable table;
      require_c_( turn_into_csv_table_o( csvData, &table, cfg, es ) );
      println_bytes( "table:", table.data );

      cRecorder* rec = &recorder_c_( 512 );
      oCsvRow row;
      iterate_csv_rows_o_( itr, &row, &table )
      {
         println_bytes( "row:", row.data );
         cChars cell;
         iterate_csv_cells_o_( itr, &cell, &row )
         {
            record_chars_c( rec, cell );
            record_char_c( rec, '-' );
         }
         record_char_c( rec, '|' );
      }

      println_bytes( "recorded:", recorded_bytes_c( rec ) );
      expect_c_( recorded_is_c( rec, t->exp ) );
   }

   return finish_tap_c_();
}