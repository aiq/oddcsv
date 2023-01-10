#include "oddcsv/oCsvCell.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

cChars decode_csv_cell_chars_o( oCsvCell const cell[static 1], cVarChars buf )
{
   return c_c( "" );
}

CString* decode_csv_cell_o( oCsvCell const cell[static 1] )
{
   return NULL;
}

/*******************************************************************************

*******************************************************************************/

bool csv_cell_is_o( oCsvCell const cell[static 1], cChars chars )
{
   return false;
}

char const* next_csv_cell_rune_o( oCsvCell const cell[static 1],
                                  char const* itr,
                                  cRune r[static 1] )
{
   itr = next_rune_c( cell->raw, itr, r );
   if ( not points_into_c_( cell->raw, itr ) ) return NULL;

   if ( r->c[0] == '"' )
   {
      itr = next_rune_c( cell->raw, itr, r );
      if ( not points_into_c_( cell->raw, itr ) ) return NULL;

      if ( r->c[0] != '"' ) return NULL;
   }

   return itr;
}