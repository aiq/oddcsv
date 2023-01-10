#ifndef ODDCSV_OCSVCELL_H
#define ODDCSV_OCSVCELL_H

#include "clingo/string/CString.h"
#include "oddcsv/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvCell
{
   cChars quoted;
   cChars raw;
   int64_t byteLength;
   int64_t length;
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

ODDCSV_API cChars decode_csv_cell_chars_o( oCsvCell const cell[static 1],
                                           cVarChars buf );

ODDCSV_API CString* decode_csv_cell_o( oCsvCell const cell[static 1] );

/*******************************************************************************

*******************************************************************************/

#define csv_cell_is_o_( Cell, Cstr )                                           \
   csv_cell_is_o( (Cell), c_c( Cstr ) )
ODDCSV_API bool csv_cell_is_o( oCsvCell const cell[static 1],
                               cChars chars );

#define iterate_csv_cell_o_( Itr, Rune, Cell )                                 \
   for ( char const* Itr = next_csv_cell_rune_o( Cell, NULL, &Rune );          \
         Itr != NULL;                                                          \
         Itr = next_csv_cell_rune_o( Cell, Itr, &Rune ) )

char const* next_csv_cell_rune_o( oCsvCell const cell[static 1],
                                  char const* itr,
                                  cRune r[static 1] );

#endif