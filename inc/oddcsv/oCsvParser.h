#ifndef ODDCSV_OCSVPARSER_H
#define ODDCSV_OCSVPARSER_H

#include "clingo/io/cScanner.h"
#include "oddcsv/apidecl.h"
#include "oddcsv/oCsvCell.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oCsvParseCfg
{
   cRune sep;
   cRune comment;
   bool trim;
};
typedef struct oCsvParseCfg oCsvParseCfg;

struct oCsvParser
{
   oCsvParseCfg cfg;
   cScanner sca;
   bool finRow;
   char const* err;
};
typedef struct oCsvParser oCsvParser;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define csv_parse_cfg_o_( Sep, ... )                                           \
   (oCsvParseCfg){ .sep=rune_c( Sep ), __VA_ARGS__ }

#define init_csv_parser_o_( Parser, Sep, Csv )                                 \
   init_csv_parser_o_( (Parser), csv_parse_cfg_o_( Sep ), (Csv) )
ODDCSV_API bool init_csv_parser_o( oCsvParser p[static 1],
                                   oCsvParseCfg cfg,
                                   cChars csv );

/*******************************************************************************

*******************************************************************************/

ODDCSV_API bool finished_csv_o( oCsvParser p[static 1] );

ODDCSV_API bool finished_csv_row_o( oCsvParser p[static 1] );

ODDCSV_API bool view_csv_cell_o( oCsvParser p[static 1],
                                 oCsvCell cell[static 1] );

ODDCSV_API bool view_csv_row_o( oCsvParser p[static 1],
                                oVarCsvRow row[static 1] );

#endif