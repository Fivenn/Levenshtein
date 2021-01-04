cmake_minimum_required (VERSION 3.10 FATAL_ERROR)

#########################################################################
# BUILD base bin
#########################################################################
add_executable(levenshteinBin levenshtein-run.cpp)

target_link_libraries(levenshteinBin PRIVATE ${PROJECT_NAME}::optionsParser)
target_link_libraries(levenshteinBin PRIVATE ${PROJECT_NAME}::useful)
target_link_libraries(levenshteinBin PRIVATE ${PROJECT_NAME}::levenshtein)

PT_set_compile_options(levenshteinBin)
set_target_properties(levenshteinBin PROPERTIES OUTPUT_NAME levenshtein)
PT_set_install(levenshteinBin)
