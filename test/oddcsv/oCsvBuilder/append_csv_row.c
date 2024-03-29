#include "clingo/lang/expect.h"
#include "oddcsv/oCsvBuilder.h"

TEMP_SLICE_C_(
   test,
   {
      oCsvBuildCfg cfg;
      cCharsSlice row;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

#define c_ csv_build_cfg_o_

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( c_( "," ), cs_c_( "abc" ), "abc\n" ),
      t_( c_( ",", .useCRLF=true ), cs_c_( "abc" ), "abc\r\n" ),
      t_( c_( "," ), cs_c_( "\"a\"b\"" ), "\"\"\"a\"\"b\"\"\"\n" ),
      t_( c_( "," ), cs_c_( " abc", "  d  ", "ef" ), " abc,  d  ,ef\n" ),
      t_( c_( ",", .quoteSpace=true ), cs_c_( " abc", "  d  ", "ef" ), "\" abc\",\"  d  \",ef\n" ),
      t_( c_( "," ), cs_c_( "abc,def" ), "\"abc,def\"\n" ),
      t_( c_( "," ), cs_c_( "abc", "def" ), "abc,def\n"),
      t_( c_( "," ), cs_c_( "abc\ndef" ), "\"abc\ndef\"\n" ),
      t_( c_( "," ), cs_c_( "" ), "\n" ),
      t_( c_( "," ), cs_c_( "", "" ), ",\n" ),
      t_( c_( "," ), cs_c_( "", "", "" ), ",,\n" ),
      t_( c_( "," ), cs_c_( "", "", "a" ), ",,a\n" ),
      t_( c_( "," ), cs_c_( "", "a", "" ), ",a,\n" ),
      t_( c_( "," ), cs_c_( "", "a", "a" ), ",a,a\n" ),
      t_( c_( "," ), cs_c_( "a", "", "" ), "a,,\n" ),
      t_( c_( "," ), cs_c_( "a", "", "a" ), "a,,a\n" ),
      t_( c_( "," ), cs_c_( "a", "a", "" ), "a,a,\n" ),
      t_( c_( "," ), cs_c_( "a", "a", "a" ), "a,a,a\n" ),
      t_( c_( "," ), cs_c_( "\\." ), "\\.\n" ),
      t_( c_( "|" ), cs_c_( "a", "a", "" ), "a|a|\n" ),
      t_( c_( "|" ), cs_c_( ",", ",", "" ), ",|,|\n" )
   );

   for_each_c_( test const*, t, tests )
   {
      oCsvBuilder* b = &(oCsvBuilder){0};
      require_c_( init_csv_builder_o( b, t->cfg, 256 ) );
      require_c_( append_csv_row_o( b, t->row ) );
      cChars csv = built_csv_o( b );
      bool res =  chars_is_c( csv, t->exp );
      tap_descf_c( res, "expected '%s', got '%s'", t->exp, csv.v );
      cleanup_csv_builder_o( b );
   }

   return finish_tap_c_();
}