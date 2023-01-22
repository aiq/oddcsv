#include "clingo/lang/expect.h"
#include "oddcsv/oCsvTable.h"

TEMP_SLICE_C_(
   test,
   {
      cCharsSlice cells;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( cs_c_( "abc", "def" ), "abc|def|" ),
      t_( cs_c_( "abc", "", "def" ), "abc||def|" ),
      t_( cs_c_( "abc", "def", "" ), "abc|def||" ),
      t_( cs_c_( "", "", "" ), "|||" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 256 );
      for_each_c_( cChars const*, chars, t->cells )
      {
         record_chars_c( rec, *chars );
         if ( chars != rbegin_c_( t->cells ) )
         {
            record_char_c( rec, 0x1F );
         }
      }

      cRecorder* resRec = &recorder_c_( 256 );
      oCsvRow row = { .data=recorded_bytes_c( rec ), t->cells.s };
      cChars cell;
      iterate_csv_cells_o_( itr, &cell, &row )
      {
         record_chars_c( resRec, cell );
         record_char_c( resRec, '|' );
      }

      expect_c_( recorded_is_c( resRec, t->exp ) );
   }

   return finish_tap_c_();
}