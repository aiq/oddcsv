#include "oddcsv/oCsvParser.h"

#include "clingo/lang/error.h"

/*******************************************************************************

*******************************************************************************/

static void skip_sep( oCsvParser p[static 1] )
{
   if ( p->cfg.trim )
      move_if_char_c( &(p->sca), ' ' );

   move_if_rune_c( &(p->sca), p->cfg.sep );

   if ( p->cfg.trim )
      move_if_char_c( &(p->sca), ' ' );
}

static bool on_cell_end( oCsvParser p[static 1] )
{
   return on_rune_c( &(p->sca), p->cfg.sep ) or
          on_char_c( &(p->sca), '\n' ) or
          on_char_c( &(p->sca), '\r' ) or
          p->sca.space == 0;
}

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool init_csv_parser_o( oCsvParser p[static 1], oCsvParseCfg cfg, cChars full )
{
   p->cfg = cfg;
   p->sca = make_scanner_c_( full.s, full.v );
   p->err = cNoError_;
   return true;
}

/*******************************************************************************

*******************************************************************************/

bool finished_csv_o( oCsvParser p[static 1] )
{
   return p->sca.space == 0 or
          unscanned_is_c( &(p->sca), "\n" ) or
          unscanned_is_c( &(p->sca), "\r\n" );
}

bool move_to_next_csv_row_o( oCsvParser p[static 1] )
{
   return move_if_char_c( &(p->sca), '\n' ) or
          move_if_chars_c_( &(p->sca), "\r\n" );
}

bool in_csv_row_o( oCsvParser p[static 1] )
{
   return not on_char_c( &(p->sca), '\n' ) and
          not on_char_c( &(p->sca), '\r' ) and
          p->sca.space != 0;;
}

bool view_raw_csv_cell_o( oCsvParser p[static 1], cChars cell[static 1] )
{
   skip_sep( p );

   char const* beg = p->sca.mem;
   if ( !on_char_c( &(p->sca), '"' ) )
   {
      if ( not on_cell_end( p ) )
      {
         move_scanner_c( &(p->sca), 1 );
      }
      char const* end = p->sca.mem;
      *cell = (cChars)atween_c_( beg, end );

      if ( p->cfg.trim )
      {
         *cell = trim_any_char_right_c_( *cell , " " );
      }
      return true;
   }

   move_scanner_c( &(p->sca), 1 );
   while ( true )
   {
      if ( not move_to_char_c( &(p->sca), '"' ) and
           not on_char_c( &(p->sca), '"' ) )
      {
         return false; // ERROR: missing closed "
      }
      move_scanner_c( &(p->sca), 1 );
      if ( move_if_char_c( &(p->sca), '"' ) )
      {
         continue;
      }

      char const* end = p->sca.mem;
      if ( p->cfg.trim )
         move_if_char_c( &(p->sca), ' ' );

      if ( not on_cell_end( p ) )
      {
         return false; // ERROR: invalid cell end
      }

      *cell = (cChars)atween_c_( beg, end );
      return true;
   }
}

/*******************************************************************************

*******************************************************************************/

static bool clear_string_list( CStringList* row )
{
   cVecInfo const* info = info_of_string_list_c( row );
   while ( info->count > 0 )
   {
      if ( not remove_from_string_list_c( row, info->count-1 ) )
         return false;
   }
   return true;
}

bool parse_csv_string_row_o( oCsvParser p[static 1], CStringList* row )
{
   if ( not clear_string_list( row ) )
   {
      return false;
   }

   while ( in_csv_row_o( p ) )
   {
      cChars cell;
      if ( not view_raw_csv_cell_o( p, &cell ) )
      {
         return false;
      }

      cRecorder* rec = &recorder_c_( 8 );
      if ( not alloc_recorder_mem_c( rec, cell.s+1 ) )
      {
         return false;
      }

      store_raw_csv_cell_o( cell, rec );
      record_char_c( rec, '\0' );
      if ( rec->space > 0 )
      {
         if ( not realloc_recorder_mem_c( rec, rec->pos ) )
         {
            free_recorder_mem_c( rec );
            return false;
         }
      }

      reset_recorder_c( rec );
      CString* str = adopt_cstr_c( rec->mem );
      if ( str == NULL )
      {
         free_recorder_mem_c( rec );
         return false;
      }

      if ( not add_to_string_list_c( row, str ) )
      {
         release_c( str );
         return false;
      }
   }

   return true;
}