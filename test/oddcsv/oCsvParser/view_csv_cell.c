#include "clingo/lang/expect.h"
#include "oddcsv/oCsvParser.h"

TEMP_SLICE_C_(
   test,
   {
      oCsvParseCfg cfg;
      char const* csv;
      char cellSep;
      char lineSep;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

#define c_( Sep, ... ) (oCsvParseCfg){ .sep=rune_c( Sep ), __VA_ARGS__ }

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_( "," ), "a,b,c", '_', '|', "a_b_c" ),
      t_( c_( "," ), "a,b\nc,d\n", '_', '|', "a_b|c_d" ),
      t_( c_( ";" ), ";a\nb;", '_', '|', "_a|b_" ),
      t_( c_( "," ), ",a\r\nb,\r\n,c\r\n", '_', '|', "_a|b_|_c" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 256 );
      oCsvParser p;
      require_c_( init_csv_parser_o( &p, t->cfg, c_c( t->csv ) ) );
      while ( not finished_csv_o( &p ) )
      {
         bool first = true;
         while ( not finished_csv_row_o( &p ) )
         {
            if ( not first )
            {
               record_char_c( rec, t->cellSep );
            }
            oCsvCell cell;
            require_c_( view_csv_cell_o( &p, &cell ) );
            record_chars_c( rec, cell.x );
            first = false;
         }
         if ( not finished_csv_o( &p ) )
         {
            record_char_c( rec, t->lineSep );
         }
      }
      cChars tmp = recorded_chars_c( rec );
      bool res =  chars_is_c( tmp, t->exp );
      tap_descf_c( res, "expected '%s', got '%s'", t->exp, tmp.v );
   }

   return finish_tap_c_();
}