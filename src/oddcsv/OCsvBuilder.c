#include "oddcsv/OCsvBuilder.h"

#include "clingo/io/write_type.h"
#include "clingo/string/CStringBuilder.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct OCsvBuilder
{
   CStringBuilder* b;
   cRune sep;
   bool useCRLF;
   int64_t count;
};

static inline void cleanup( void* instance )
{
   OCsvBuilder* b = instance;
   release_c( b->b );
}

cMeta const O_CsvBuilderMeta = {
   .desc = stringify_c_( OCsvBuilder ),
   .cleanup = &cleanup
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

OCsvBuilder* new_csv_builder_o( cRune sep )
{
   return make_csv_builder_o( sep, false );
}

OCsvBuilder* make_csv_builder_o( cRune sep, bool useCRLF )
{
   OCsvBuilder* b = new_object_c_( OCsvBuilder, &O_CsvBuilderMeta );
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

   b->sep = sep;
   b->useCRLF = useCRLF;
   b->count = 0;

   return b;
}

/*******************************************************************************

*******************************************************************************/

bool csv_builder_has_error_o( OCsvBuilder* b )
{
   return false;
}

bool push_csv_builder_error_o( cErrorStack es[static 1],
                               OCsvBuilder* b )
{
   return false;
}

/*******************************************************************************

*******************************************************************************/

cChars built_csv_o( OCsvBuilder* b )
{
   must_exist_c_( b );
   return built_chars_c( b->b );
}

char const* built_csv_cstr_o( OCsvBuilder* b )
{
   must_exist_c_( b );
   return built_cstr_c( b->b );
}

/*******************************************************************************

*******************************************************************************/

bool append_csv_row_o( OCsvBuilder* b, cCharsSlice row )
{
   must_exist_c_( b );
   for_each_c_( cChars const*, itr, row )
   {
      if ( not append_csv_chars_cell_o( b, *itr ) )
         return false;
   }
   return finish_csv_row_o( b );
}

/*******************************************************************************

*******************************************************************************/

static cRune nRune = build_rune_c_( '\n', 0, 0, 0 );
static cRune crRune = build_rune_c_( '\r', 0, 0, 0 );
static cRune dqRune = build_rune_c_( '"', 0, 0, 0 );

static bool needs_quotes( cChars chars, cRune sep )
{
   cRune r;
   iterate_runes_c_( itr, r, chars )
   {
      if ( eq_rune_c( r, nRune ) or
           eq_rune_c( r, crRune ) or
           eq_rune_c( r, dqRune ) or
           eq_rune_c( r, sep ) )
      {
         return true;
      }
   }
   return false;
}

bool append_csv_chars_cell_o( OCsvBuilder* b, cChars chars )
{
   must_exist_c_( b );

   if ( b->count > 0 )
   {
      if ( not append_rune_c( b->b, b->sep ) )
         return false;
   }

   if ( not needs_quotes( chars, b->sep ) )
   {
      b->count++;
      return append_chars_c( b->b, chars );
   }

   return false;
}

bool append_csv_double_cell_o( OCsvBuilder* b,
                               double value,
                               char const fmt[static 1] )
{
   must_exist_c_( b );
   cRecorder* rec = &recorder_c_( 256 );
   if ( not write_double_c( rec, value, fmt ) )
   {
      return false;
   }

   return append_csv_chars_cell_o( b, recorded_chars_c( rec ) );
}

bool append_csv_int64_cell_o( OCsvBuilder* b,
                              int64_t value,
                              char const fmt[static 1] )
{
   must_exist_c_( b );
   cRecorder* rec = &recorder_c_( 256 );
   if ( not write_int64_c( rec, value, fmt ) )
   {
      return false;
   }
   return append_csv_chars_cell_o( b, recorded_chars_c( rec ) );
}

bool append_csv_uint64_cell_o( OCsvBuilder* b,
                               uint64_t value,
                               char const fmt[static 1] )
{
   must_exist_c_( b );
   cRecorder* rec = &recorder_c_( 256 );
   if ( not write_uint64_c( rec, value, fmt ) )
   {
      return false;
   }
   return append_csv_chars_cell_o( b, recorded_chars_c( rec ) );
}

bool finish_csv_row_o( OCsvBuilder* b )
{
   must_exist_c_( b );

   b->count = 0;
   bool res = true;
   if ( b->useCRLF )
   {
      res &= append_char_c( b->b, '\r' );
   }
   res &= append_char_c( b->b, '\n' );
   return res;
}