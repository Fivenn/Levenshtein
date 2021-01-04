#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Levenshtein::easylogging++" for configuration "Debug"
set_property(TARGET Levenshtein::easylogging++ APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Levenshtein::easylogging++ PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Levenshtein/libeasylogging++.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Levenshtein::easylogging++ )
list(APPEND _IMPORT_CHECK_FILES_FOR_Levenshtein::easylogging++ "${_IMPORT_PREFIX}/lib/Levenshtein/libeasylogging++.a" )

# Import target "Levenshtein::useful" for configuration "Debug"
set_property(TARGET Levenshtein::useful APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Levenshtein::useful PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Levenshtein/libuseful.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Levenshtein::useful )
list(APPEND _IMPORT_CHECK_FILES_FOR_Levenshtein::useful "${_IMPORT_PREFIX}/lib/Levenshtein/libuseful.a" )

# Import target "Levenshtein::optionsParser" for configuration "Debug"
set_property(TARGET Levenshtein::optionsParser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Levenshtein::optionsParser PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Levenshtein/liboptionsParser.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Levenshtein::optionsParser )
list(APPEND _IMPORT_CHECK_FILES_FOR_Levenshtein::optionsParser "${_IMPORT_PREFIX}/lib/Levenshtein/liboptionsParser.a" )

# Import target "Levenshtein::levenshtein" for configuration "Debug"
set_property(TARGET Levenshtein::levenshtein APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Levenshtein::levenshtein PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Levenshtein/liblevenshtein.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Levenshtein::levenshtein )
list(APPEND _IMPORT_CHECK_FILES_FOR_Levenshtein::levenshtein "${_IMPORT_PREFIX}/lib/Levenshtein/liblevenshtein.a" )

# Import target "Levenshtein::levenshteinBin" for configuration "Debug"
set_property(TARGET Levenshtein::levenshteinBin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Levenshtein::levenshteinBin PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/levenshtein"
  )

list(APPEND _IMPORT_CHECK_TARGETS Levenshtein::levenshteinBin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Levenshtein::levenshteinBin "${_IMPORT_PREFIX}/bin/levenshtein" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
