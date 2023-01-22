#include "clingo/lang/expect.h"
#include "oddcsv/oCsvCell.h"

TEMP_SLICE_C_(
   test,
   {
      char const* cell;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "abc", "abc" ),
      t_( "\"\"\"a\"\"b\"\"\"", "\"a\"b\"" ),
      t_( "\"abc\ndef\"", "abc\ndef" )
   );

   for_each_c_( test const*, t, tests )
   {
      oCsvCell cell = { .x=c_c( t->cell ) };
      cVarChars buf = var_chars_c_( 256 );
      cChars tmp = decode_csv_cell_chars_o( cell, buf );
      require_c_( not is_invalid_c_( tmp ) );

      bool res =  chars_is_c( tmp, t->exp );
      tap_descf_c( res, "expected '%s', got '%s'", t->exp, tmp.v );
   }

   return finish_tap_c_();
}