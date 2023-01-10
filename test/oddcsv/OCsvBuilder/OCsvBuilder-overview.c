#include "clingo/lang/expect.h"
#include "oddcsv/OCsvBuilder.h"

#include "clingo/io/print.h"

TEMP_SLICE_C_(
   hero,
   {
      char const* name;
      char const* alter_ego;
      int64_t year;
   }
)
#define h_( ... ) ((hero){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   OCsvBuilder* b = new_csv_builder_o_( "," );

   cCharsSlice header = cs_c_( "name", "alter_ego", "year" );
   heroSlice heros = slice_c_( hero,
      h_( "Superman", "Clark Kent", 1938 ),
      h_( "Batman", "Bruce Wayne", 1939 ),
      h_( "Wonder Woman", "Diana Prince", 1941 )
   );

   append_csv_row_o( b, header );
   for_each_c_( hero const*, hero, heros )
   {
      append_csv_cell_o_( b, hero->name );
      append_csv_cell_o_( b, hero->alter_ego );
      append_csv_int64_cell_o_( b, hero->year );
      finish_csv_row_o( b );

      if ( csv_builder_has_error_o( b ) )
      {
         cErrorStack* es = &error_stack_c_( 256 );
         push_csv_builder_error_o( es, b );
         println_c_( "error occured: {e}", es->err );
         break;
      }
   }

   cChars csv = built_csv_o( b );
   char const* exp = "name,alter_ego,year\n"
                     "Superman,Clark Kent,1938\n"
                     "Batman,Bruce Wayne,1939\n"
                     "Wonder Woman,Diana Prince,1941\n";
   bool res =  chars_is_c( csv, exp );
   tap_descf_c( res, "expected '%s', got '%s'", exp, csv.v );

   release_c( b );
   return finish_tap_c_();
}