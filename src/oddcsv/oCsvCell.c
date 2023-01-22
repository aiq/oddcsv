#include "oddcsv/oCsvCell.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

extern inline bool csv_cell_is_quoted_o( oCsvCell cell );

char const* next_csv_cell_rune_o( oCsvCell cell,
                                  char const* itr,
                                  cRune r[static 1] )
{
   if ( is_empty_c_( cell.x ) ) return NULL;

   if ( first_c_( cell.x ) != '"' )
   {
      return next_rune_c( cell.x, itr, r );
   }

   cell.x = (cChars){ .s=cell.x.s-2, .v=++cell.x.v };
   itr = next_rune_c( cell.x, itr, r );
   if ( itr != NULL and rune_is_c( *r, "\"" ) )
   {
      itr = next_rune_c( cell.x, itr, r );
      if ( not rune_is_c( *r, "\"" ) )
         return NULL;
   }

   return itr;
}

cChars decode_csv_cell_chars_o( oCsvCell cell, cVarChars buf )
{
   cRecorder* rec = &make_recorder_c_( buf.s, buf.v );

   cRune r;
   iterate_csv_cell_o_( itr, &r, cell )
   {
      if ( not record_rune_c( rec, r ) )
         return (cChars)invalid_c_();
   }

   return recorded_chars_c( rec );
}

int64_t csv_cell_byte_length_o( oCsvCell cell )
{
   int64_t len = 0;

   cRune r;
   iterate_csv_cell_o_( itr, &r, cell )
   {
      len += rune_size_c( r );
   }

   return len;
}