################################################################################
# INC_FILES
################################################################################
set( INC_FILES
   ${INC_DIR}/oddcsv/apidecl.h

   ${INC_DIR}/oddcsv/misc.h
   ${INC_DIR}/oddcsv/OCsvBuilder.h
   ${INC_DIR}/oddcsv/oCsvParser.h
   ${INC_DIR}/oddcsv/oCsvTable.h
)

################################################################################
# SRC_FILES
################################################################################
set( SRC_FILES
   ${SRC_DIR}/oddcsv/misc.c
   ${SRC_DIR}/oddcsv/OCsvBuilder.c
   ${SRC_DIR}/oddcsv/oCsvParser.c
   ${SRC_DIR}/oddcsv/oCsvTable.c
)

################################################################################
# TEST_FILES
################################################################################
set( TEST_FILES
   # misc
   ${TEST_DIR}/oddcsv/misc/store_raw_csv_cell.c
   # OCsvBuilder
   ${TEST_DIR}/oddcsv/OCsvBuilder/append_csv_row.c
   ${TEST_DIR}/oddcsv/OCsvBuilder/OCsvBuilder-overview.c
   # oCsvCell
#   ${TEST_DIR}/oddcsv/OJsonBuilder/append_json_bool_value.c
   # oCsvParser
   ${TEST_DIR}/oddcsv/oCsvParser/view_raw_csv_cell.c
)

################################################################################
# APP_FILES
################################################################################
set( APP_FILES
#   ${APP_DIR}/ebml-navi/ebml-navi.c
)
