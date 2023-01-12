#include "clingo/lang/expect.h"
#include "oddcsv/misc.h"

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
      cRecorder* rec = &recorder_c_( 256 );
      require_c_( store_raw_csv_cell_o( c_c( t->cell ), rec ) );

      cChars tmp = recorded_chars_c( rec );
      bool res =  chars_is_c( tmp, t->exp );
      tap_descf_c( res, "expected '%s', got '%s'", t->exp, tmp.v );
   }

   return finish_tap_c_();
}