cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)

message("generator is set to ${CMAKE_GENERATOR}")

set(LIBNAME "StringMatchLib")
set(TESTNAME "StringMatchTests")

set(LIB_MAJOR_VERS "1")
set(LIB_MINOR_VERS "0")
set(LIB_PATCH_VERS "0")
include_directories(src)

#build source
project(${LIBNAME}
        VERSION  ${LIB_MAJOR_VERS}.${LIB_MINOR_VERS}.${LIB_PATCH_VERS})
add_subdirectory(src)

project(${TESTNAME})
add_subdirectory(tests)
enable_testing()
add_test(${TESTNAME} "test/bin/${TESTNAME}")

project(StringMatch)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(src)
add_executable(StringMatch main.cpp)
target_link_libraries(StringMatch ${LIBNAME})
