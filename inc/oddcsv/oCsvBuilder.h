#ifndef ODDCSV_OCSVBUILDER_H
#define ODDCSV_OCSVBUILDER_H

#include "clingo/lang/CObject.h"
#include "clingo/lang/error.h"
#include "clingo/string/cStringBuilder.h"
#include "oddcsv/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvBuildCfg
{
   cRune sep;
   bool useCRLF;
   bool quoteSpace;
};
typedef struct oCsvBuildCfg oCsvBuildCfg;

struct oCsvBuilder
{
   cStringBuilder b;
   oCsvBuildCfg cfg;
   int64_t count;
};
typedef struct oCsvBuilder oCsvBuilder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define csv_build_cfg_o_( Sep, ... )                                           \
   (oCsvBuildCfg){ .sep=rune_c( Sep ), __VA_ARGS__ }

#define init_csv_builder_o_( Builder, Sep, Cap )                              \
   init_csv_builder_o( (Builder), csv_build_cfg_o_( Sep ), (Cap) )
ODDCSV_API inline bool init_csv_builder_o( oCsvBuilder b[static 1],
                                           oCsvBuildCfg cfg,
                                           int64_t cap )
{
   b->cfg = cfg;
   return init_string_builder_c( &b->b, cap );
}

ODDCSV_API inline void cleanup_csv_builder_o( oCsvBuilder b[static 1] )
{
   return cleanup_string_builder_c( &b->b );
}

/*******************************************************************************

*******************************************************************************/

ODDCSV_API bool csv_builder_has_error_o( oCsvBuilder b[static 1] );

ODDCSV_API bool push_csv_builder_error_o( cErrorStack es[static 1],
                                          oCsvBuilder b[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API inline cChars built_csv_o( oCsvBuilder b[static 1] )
{
   return built_chars_c( &(b->b) );
}

ODDCSV_API inline char const* built_csv_cstr_o( oCsvBuilder b[static 1] )
{
   return built_cstr_c( &(b->b) );
}

/*******************************************************************************

*******************************************************************************/

#define append_csv_cell_o_( B, Cstr )                                          \
   append_csv_cell_o( (B), c_c( Cstr ) )
ODDCSV_API bool append_csv_cell_o( oCsvBuilder b[static 1], cChars chars );

ODDCSV_API bool append_csv_row_o( oCsvBuilder b[static 1], cCharsSlice row );

ODDCSV_API bool finish_csv_row_o( oCsvBuilder b[static 1] );

/*******************************************************************************

*******************************************************************************/

#define append_csv_double_cell_o_( B, Value )                                  \
   append_csv_double_cell_o( (B), (Value), "" )
ODDCSV_API bool append_csv_double_cell_o( oCsvBuilder b[static 1],
                                          double value,
                                          char const fmt[static 1] );

#define append_csv_int64_cell_o_( B, Value )                                   \
   append_csv_int64_cell_o( (B), (Value), "" )
ODDCSV_API bool append_csv_int64_cell_o( oCsvBuilder b[static 1],
                                         int64_t value,
                                         char const fmt[static 1] );

#define append_csv_uint64_cell_o_( B, Value )                                  \
   append_csv_uint64_cell_o( (B), (Value), "" )
ODDCSV_API bool append_csv_uint64_cell_o( oCsvBuilder b[static 1],
                                          uint64_t value,
                                          char const fmt[static 1] );

#endif