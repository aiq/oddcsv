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

ODDCSV_API cChars decode_csv_chars_o( oCsvCell const cell[static 1],
                                      cVarChars buf );

ODDCSV_API CString* decode_csv_string_o( oCsvCell const cell[static 1] );

/*******************************************************************************

*******************************************************************************/

#define csv_cell_is_o_( Cell, Cstr )                                           \
   csv_cell_is_o( (Cell), c_c( Cstr ) )
ODDCSV_API bool csv_cell_is_o( oCsvCell const cell[static 1],
                               cChars chars );

#endif