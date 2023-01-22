#ifndef ODDCSV_OCSVCELL_H
#define ODDCSV_OCSVCELL_H

#include "clingo/io/cRecorder.h"
#include "oddcsv/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvCell
{
   cChars x;
};
typedef struct oCsvCell oCsvCell;

SLICES_C_(
   oCsvCell,   // Type
   oCsvRow,    // SliceType
   oVarCsvRow  // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDCSV_API inline bool csv_cell_is_quoted_o( oCsvCell cell )
{
   return not is_empty_c_( cell.x ) and first_c_( cell.x ) != '"';
}

#define iterate_csv_cell_o_( Itr, RunePtr, Cell )                              \
   for ( char const* Itr = next_csv_cell_rune_o( Cell, NULL, RunePtr );        \
         Itr != NULL;                                                          \
         Itr = next_csv_cell_rune_o( Cell, Itr, RunePtr ) )

ODDCSV_API char const* next_csv_cell_rune_o( oCsvCell cell,
                                             char const* itr,
                                             cRune r[static 1] );

ODDCSV_API cChars decode_csv_cell_chars_o( oCsvCell cell,
                                           cVarChars buf );

ODDCSV_API int64_t csv_cell_byte_length_o( oCsvCell cell );

#endif