#include "oddcsv/oCsvParser.h"

#include "clingo/lang/error.h"

/*******************************************************************************

*******************************************************************************/

static void skip_spaces( oCsvParser p[static 1] )
{
   if ( p->cfg.trim )
      move_if_char_c( &(p->sca), ' ' );
}

static void skip_cell_end( oCsvParser p[static 1] )
{
   if ( move_if_rune_c( &(p->sca), p->cfg.sep ) )
      return;

   if ( move_if_char_c( &(p->sca), '\n' ) or
        move_if_chars_c_( &(p->sca), "\r\n" ) )
   {
      p->finRow = true;
      return;
   }

   p->finRow = finished_csv_o( p );
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
   p->finRow = false;
   p->err = cNoError_;
   return true;
}

/*******************************************************************************

*******************************************************************************/

bool finished_csv_o( oCsvParser p[static 1] )
{
   bool res = p->sca.space == 0;
   p->finRow = false;
   return res;
}

bool finished_csv_row_o( oCsvParser p[static 1] )
{
   return p->finRow;
}

bool view_csv_cell_o( oCsvParser p[static 1], oCsvCell cell[static 1] )
{
   skip_spaces( p );

   char const* beg = p->sca.mem;
   if ( !on_char_c( &(p->sca), '"' ) )
   {
      while ( not on_cell_end( p ) )
      {
         move_scanner_c( &(p->sca), 1 );
      }
      char const* end = p->sca.mem;
      cell->x = (cChars)atween_c_( beg, end );

      if ( p->cfg.trim )
      {
         cell->x = trim_any_char_right_c_( cell->x, " " );
      }
      skip_cell_end( p );
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

      cell->x = (cChars)atween_c_( beg, end );
      skip_spaces( p );
      skip_cell_end( p );
      return true;
   }
}

bool view_csv_row_o( oCsvParser p[static 1], oVarCsvRow row[static 1] )
{
   int64_t i = 0;
   while ( not finished_csv_row_o( p ) )
   {
      if ( i >= row->s )
      {
         return false; // ERROR: not inough space in row
      }

      oCsvCell cell;
      if ( not view_csv_cell_o( p, &cell ) )
      {
         return false; // ERROR: pass-through
      }

      row->v[i] = cell;
      ++i;
   }
   p->finRow = false;
   row->s = i;
   return true;
}

/*******************************************************************************

*******************************************************************************/
/*
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
*/
bool parse_csv_string_row_o( oCsvParser p[static 1], CStringList* row )
{
   return false;
}