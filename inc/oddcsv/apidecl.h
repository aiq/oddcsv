#ifndef ODDCSV_APIDECL_H
#define ODDCSV_APIDECL_H

#ifdef ODDCSV_STATIC_DEFINE
#  define ODDCSV_API
#  define ODDCSV_NO_EXPORT
#else
#  ifdef _WIN32
#    ifndef ODDCSV_API
#      ifdef ODDCSV_EXPORTS
#        define ODDCSV_API __declspec(dllexport)
#      else
#        define ODDCSV_API __declspec(dllimport)
#      endif
#    endif
#  else
#    define ODDCSV_API
#    define ODDCSV_NO_EXPORT
#  endif
#
#  ifndef ODDCSV_NO_EXPORT
#    define ODDCSV_NO_EXPORT 
#  endif
#endif

#endif