#include "clingo/lang/expect.h"
#include "oddcsv/OCsvBuilder.h"

TEMP_SLICE_C_(
   test,
   {
      OCsvBuilder* b;
      cCharsSlice row;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

#define b_( Sep, ... ) make_csv_builder_o_( .sep=rune_c( Sep ), __VA_ARGS__ )

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( b_( "," ), cs_c_( "abc" ), "abc\n" ),
      t_( b_( ",", .useCRLF=true ), cs_c_( "abc" ), "abc\r\n" ),
      t_( b_( "," ), cs_c_( "\"a\"b\"" ), "\"\"\"a\"\"b\"\"\"\n" ),
      t_( b_( "," ), cs_c_( " abc", "  d  ", "ef" ), " abc,  d  ,ef\n" ),
      t_( b_( ",", .quoteSpace=true ), cs_c_( " abc", "  d  ", "ef" ), "\" abc\",\"  d  \",ef\n" ),
      t_( b_( "," ), cs_c_( "abc,def" ), "\"abc,def\"\n" ),
      t_( b_( "," ), cs_c_( "abc", "def" ), "abc,def\n"),
      t_( b_( "," ), cs_c_( "abc\ndef" ), "\"abc\ndef\"\n" ),
      t_( b_( "," ), cs_c_( "" ), "\n" ),
      t_( b_( "," ), cs_c_( "", "" ), ",\n" ),
      t_( b_( "," ), cs_c_( "", "", "" ), ",,\n" ),
      t_( b_( "," ), cs_c_( "", "", "a" ), ",,a\n" ),
      t_( b_( "," ), cs_c_( "", "a", "" ), ",a,\n" ),
      t_( b_( "," ), cs_c_( "", "a", "a" ), ",a,a\n" ),
      t_( b_( "," ), cs_c_( "a", "", "" ), "a,,\n" ),
      t_( b_( "," ), cs_c_( "a", "", "a" ), "a,,a\n" ),
      t_( b_( "," ), cs_c_( "a", "a", "" ), "a,a,\n" ),
      t_( b_( "," ), cs_c_( "a", "a", "a" ), "a,a,a\n" ),
      t_( b_( "," ), cs_c_( "\\." ), "\\.\n" ),
      t_( b_( "|" ), cs_c_( "a", "a", "" ), "a|a|\n" ),
      t_( b_( "|" ), cs_c_( ",", ",", "" ), ",|,|\n" )
   );

   for_each_c_( test const*, t, tests )
   {
      require_c_( t->b );
      require_c_( append_csv_row_o( t->b, t->row ) );
      cChars csv = built_csv_o( t->b );
      bool res =  chars_is_c( csv, t->exp );
      tap_descf_c( res, "expected '%s', got '%s'", t->exp, csv.v );
   }

   return finish_tap_c_();
}