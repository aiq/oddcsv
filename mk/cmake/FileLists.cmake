################################################################################
# INC_FILES
################################################################################
set( INC_FILES
   ${INC_DIR}/oddcsv/apidecl.h

   ${INC_DIR}/oddcsv/OCsvBuilder.h
#   ${INC_DIR}/oddcsv/oCsvCell.h
#   ${INC_DIR}/oddcsv/oCsvParser.h
)

################################################################################
# SRC_FILES
################################################################################
set( SRC_FILES
   ${SRC_DIR}/oddcsv/OCsvBuilder.c
#   ${SRC_DIR}/oddcsv/oCsvCell.c
#   ${SRC_DIR}/oddcsv/oCsvParser.c
)

################################################################################
# TEST_FILES
################################################################################
set( TEST_FILES
   # OCsvBuilder
   ${TEST_DIR}/oddcsv/OCsvBuilder/append_csv_row.c
   ${TEST_DIR}/oddcsv/OCsvBuilder/OCsvBuilder-overview.c
   # oCsvCell
#   ${TEST_DIR}/oddcsv/OJsonBuilder/append_json_bool_value.c
   # oCsvParser
#   ${TEST_DIR}/oddjson/oJsonParser/oJsonParser-overview.c
)

################################################################################
# APP_FILES
################################################################################
set( APP_FILES
#   ${APP_DIR}/ebml-navi/ebml-navi.c
)
