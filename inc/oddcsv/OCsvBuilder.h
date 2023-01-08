#ifndef ODDCSV_OCSVBUILDER_H
#define ODDCSV_OCSVBUILDER_H

#include "clingo/lang/CObject.h"
#include "clingo/lang/error.h"
#include "clingo/type/cCharsSlice.h"
#include "clingo/type/cRune.h"
#include "oddcsv/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDCSV_API extern cMeta const O_CsvBuilderMeta;

struct OCsvBuilder;
typedef struct OCsvBuilder OCsvBuilder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define new_csv_builder_o_( Cstr )                                             \
   new_csv_builder_o( rune_c( Cstr ) )
ODDCSV_API OCsvBuilder* new_csv_builder_o( cRune sep );

ODDCSV_API OCsvBuilder* make_csv_builder_o( cRune sep, bool useCRLF );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API bool csv_builder_has_error_o( OCsvBuilder* b );

ODDCSV_API bool push_csv_builder_error_o( cErrorStack es[static 1],
                                          OCsvBuilder* b );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API cChars built_csv_o( OCsvBuilder* b );

ODDCSV_API char const* built_csv_cstr_o( OCsvBuilder* b );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API bool append_csv_row_o( OCsvBuilder* b, cCharsSlice row );

/*******************************************************************************

*******************************************************************************/

#define append_csv_chars_cell_o_( B, Cstr )                                    \
   append_csv_chars_cell_o( (B), c_c( Cstr ) )
ODDCSV_API bool append_csv_chars_cell_o( OCsvBuilder* b, cChars chars );

#define append_csv_double_cell_o_( B, Value )                                  \
   append_csv_double_cell_o( (B), (Value), "" )
ODDCSV_API bool append_csv_double_cell_o( OCsvBuilder* b,
                                          double value,
                                          char const fmt[static 1] );

#define append_csv_int64_cell_o_( B, Value )                                   \
   append_csv_int64_cell_o( (B), (Value), "" )
ODDCSV_API bool append_csv_int64_cell_o( OCsvBuilder* b,
                                         int64_t value,
                                         char const fmt[static 1] );

#define append_csv_uint64_cell_o_( B, Value )                                  \
   append_csv_uint64_cell_o( (B), (Value), "" )
ODDCSV_API bool append_csv_uint64_cell_o( OCsvBuilder* b,
                                          uint64_t value,
                                          char const fmt[static 1] );

ODDCSV_API bool finish_csv_row_o( OCsvBuilder* b );

#endif