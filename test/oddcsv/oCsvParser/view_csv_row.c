#include "clingo/lang/expect.h"
#include "oddcsv/oCsvParser.h"

TEMP_SLICE_C_(
   test,
   {

   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   return finish_tap_c_();
}