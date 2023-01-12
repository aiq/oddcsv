#include "oddcsv/misc.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

char const* next_csv_cell_rune_o( cChars cell,
                                  char const* itr,
                                  cRune r[static 1] )
{
   if ( is_empty_c_( cell ) ) return NULL;

   if ( first_c_( cell ) != '"' )
   {
      return next_rune_c( cell, itr, r );
   }

   cell = (cChars){ .s=cell.s-2, .v=++cell.v };
   itr = next_rune_c( cell, itr, r );
   if ( itr != NULL and rune_is_c( *r, "\"" ) )
   {
      itr = next_rune_c( cell, itr, r );
      if ( not rune_is_c( *r, "\"" ) )
         return NULL;
   }

   return itr;
}

bool store_raw_csv_cell_o( cChars cell, cRecorder rec[static 1] )
{
   int64_t oldPos = rec->pos;

   cRune r;
   iterate_csv_cell_o_( itr, r, cell )
   {
      if ( not record_rune_c( rec, r ) )
      {
         move_recorder_to_c( rec, oldPos );
         return false;
      }
   }
   return true;
}