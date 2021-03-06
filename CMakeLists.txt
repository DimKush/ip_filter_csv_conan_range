cmake_minimum_required(VERSION 3.12)


set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)

#set(ENV{TRAVIS_BUILD_NUMBER} 1) #plug

project(ip_filter_csv_conan_range VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.$ENV{TRAVIS_BUILD_NUMBER})
set(CMAKE_CXX_STANDARD 17)

configure_file(version.vers ${PROJECT_SOURCE_DIR}/version.h)

#include conan
include(./conanbuildinfo.cmake)
conan_basic_setup()

#include package
include(gtest.cmake)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package (Threads)

#source
add_executable( ip_filter_csv_conan_range.out
                ${PROJECT_SOURCE_DIR}/src/main.cpp
)
add_library( ip_filter_csv_lib
             ${PROJECT_SOURCE_DIR}/libSource/libSource.cpp
             ${PROJECT_SOURCE_DIR}/libSource/filters.tpp
)


#unit test
add_executable( unit_test_filter.out
                ${PROJECT_SOURCE_DIR}/src/unit.cpp
                ${PROJECT_SOURCE_DIR}/libUnitTest/libUnitTest.cpp
                ${PROJECT_SOURCE_DIR}/libUnitTest/libUnitTest.h
)


#targets source
set_target_properties( ip_filter_csv_conan_range.out ip_filter_csv_lib PROPERTIES
                       CXX_STANDARD 17
                       CXX_STANDARD_REQUIRED ON
                       COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
target_link_libraries( ip_filter_csv_conan_range.out
                       ip_filter_csv_lib
)
target_include_directories( ip_filter_csv_conan_range.out PUBLIC
                            ${PROJECT_SOURCE_DIR}/libSource
)


#targets unit tests
target_link_libraries( unit_test_filter.out
                       googletestLib
                       ${CMAKE_THREAD_LIBS_INIT}
                       ip_filter_csv_lib
)
target_include_directories(unit_test_filter.out PUBLIC 
                            ${PROJECT_SOURCE_DIR}/libSource
                            ${PROJECT_SOURCE_DIR}/libUnitTest
)


install(TARGETS ip_filter_csv_conan_range.out RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dimkysh@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

macro (create_test target)
    add_test(NAME ${target} COMMAND $<TARGET_FILE:unit_test_filter.out>)
endmacro(create_test)

create_test(unit_test)
