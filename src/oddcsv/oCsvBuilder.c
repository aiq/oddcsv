#include "oddcsv/oCsvBuilder.h"

#include "clingo/io/write_type.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/
/*
oCsvBuilder* new_csv_builder_o( cRune sep )
{
   return make_csv_builder_o( (oCsvBuilder){
      .sep = sep,
      .useCRLF = false
   } );
}

oCsvBuilder* make_csv_builder_o( oCsvBuilderCfg cfg )
{
   oCsvBuilder* b = new_object_c_( oCsvBuilder, &O_CsvBuilderMeta );
   if ( b == NULL )
   {
      return NULL;
   }

   b->b = new_string_builder_c();
   if ( b->b == NULL )
   {
      release_c( b );
      return NULL;
   }

   b->cfg = cfg;
   b->count = 0;

   return b;
}
*/

extern inline bool init_csv_builder_o( oCsvBuilder b[static 1],
                                       oCsvBuildCfg cfg,
                                       int64_t cap );

extern inline void cleanup_csv_builder_o( oCsvBuilder b[static 1] );

/*******************************************************************************

*******************************************************************************/

bool csv_builder_has_error_o( oCsvBuilder b[static 1] )
{
   return false;
}

bool push_csv_builder_error_o( cErrorStack es[static 1],
                               oCsvBuilder b[static 1] )
{
   return false;
}

/*******************************************************************************

*******************************************************************************/

extern inline cChars built_csv_o( oCsvBuilder b[static 1] );

extern inline char const* built_csv_cstr_o( oCsvBuilder b[static 1] );

/*******************************************************************************

*******************************************************************************/

static bool needs_quotes( cChars chars, oCsvBuildCfg cfg )
{
   cRune r;
   iterate_runes_c_( itr, &r, chars )
   {
      if ( r.c[0] == '\n' or
           r.c[0] == '\r' or
           r.c[0] == '"' or
           eq_rune_c( r, cfg.sep ) or
           ( cfg.quoteSpace and
              r.c[0] == ' '
           ) )
      {
         return true;
      }
   }
   return false;
}

bool append_csv_cell_o( oCsvBuilder b[static 1], cChars chars )
{
   must_exist_c_( b );

   if ( b->count > 0 )
   {
      if ( not append_rune_c( &b->b, b->cfg.sep ) )
         return false;
   }

   b->count++;
   if ( not needs_quotes( chars, b->cfg ) )
   {
      return append_chars_c( &b->b, chars );
   }

   if ( not append_char_c( &b->b, '"' ) )
   {
      return false;
   }
   cRune r;
   iterate_runes_c_( itr, &r, chars )
   {
      if ( not append_rune_c( &b->b, r ) )
      {
         return false;
      }
      if ( r.c[0] == '"' )
      {
         if ( not append_char_c( &b->b, '"' ) )
         {
            return false;
         }
      }
   }
   if ( not append_char_c( &b->b, '"' ) )
   {
      return false;
   }

   return true;
}

bool append_csv_row_o( oCsvBuilder b[static 1], cCharsSlice row )
{
   for_each_c_( cChars const*, itr, row )
   {
      if ( not append_csv_cell_o( b, *itr ) )
         return false;
   }
   return finish_csv_row_o( b );
}

bool finish_csv_row_o( oCsvBuilder b[static 1] )
{
   b->count = 0;
   bool res = true;
   if ( b->cfg.useCRLF )
   {
      res &= append_char_c( &b->b, '\r' );
   }
   res &= append_char_c( &b->b, '\n' );
   return res;
}

/*******************************************************************************

*******************************************************************************/

bool append_csv_double_cell_o( oCsvBuilder b[static 1],
                               double value,
                               char const fmt[static 1] )
{
   cRecorder* rec = &recorder_c_( 256 );
   if ( not write_double_c( rec, value, fmt ) )
   {
      return false;
   }

   return append_csv_cell_o( b, recorded_chars_c( rec ) );
}

bool append_csv_int64_cell_o( oCsvBuilder b[static 1],
                              int64_t value,
                              char const fmt[static 1] )
{
   cRecorder* rec = &recorder_c_( 256 );
   if ( not write_int64_c( rec, value, fmt ) )
   {
      return false;
   }
   return append_csv_cell_o( b, recorded_chars_c( rec ) );
}

bool append_csv_uint64_cell_o( oCsvBuilder b[static 1],
                               uint64_t value,
                               char const fmt[static 1] )
{
   cRecorder* rec = &recorder_c_( 256 );
   if ( not write_uint64_c( rec, value, fmt ) )
   {
      return false;
   }
   return append_csv_cell_o( b, recorded_chars_c( rec ) );
}