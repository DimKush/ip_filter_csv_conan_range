set(GOOGLETEST_ROOT  ./googletest/googletest)

message("${GOOGLETEST_ROOT}")
message("${PROJECT_SOURCE_DIR}")

include_directories(SYSTEM
    ${PROJECT_SOURCE_DIR}/googletest/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/googletest/${GOOGLETEST_ROOT}/include
    )

set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/googletest/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/googletest/${GOOGLETEST_ROOT}/src/gtest_main.cc
    )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletestLib ${GOOGLETEST_SOURCES})