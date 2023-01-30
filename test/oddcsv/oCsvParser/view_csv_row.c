#include "clingo/lang/expect.h"
#include "oddcsv/oCsvParser.h"

TEMP_SLICE_C_(
   test,
   {
      oCsvParseCfg cfg;
      char const* csv;
      char cellSep;
      char rowSep;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

#define c_ csv_parse_cfg_o_

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_( ";" ), ";a\nb;", '.', '|', ".a.|b..|" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 256 );
      oCsvParser* p = &(oCsvParser){0};
      require_c_( init_csv_parser_o( p, t->cfg, c_c( t->csv ) ) );
   
      while ( not finished_csv_o( p ) )
      {
         oVarCsvRow row = structs_c_( 16, oCsvCell );
         require_c_( view_csv_row_o( p, &row ) );

         for_each_c_( oCsvCell const*, cell, row )
         {
            record_chars_c( rec, cell->x );
            record_char_c( rec, t->cellSep );
         }
         record_char_c( rec, t->rowSep );
      }
   
      cChars tmp = recorded_chars_c( rec );
      bool res =  chars_is_c( tmp, t->exp );
      tap_descf_c( res, "expected '%s', got '%s'", t->exp, tmp.v );
   }

   return finish_tap_c_();
}