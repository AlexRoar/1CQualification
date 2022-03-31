set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src/bin)

set(SRCS
        core/algo/GeneralSearcher.cpp
        core/algo/GeneralSearcher.h
        core/details/KMP.cpp
        core/details/KMP.h
        core/algo/SmallSearcher.cpp
        core/algo/SmallSearcher.h core/algo/SingleSearcher.cpp core/algo/SingleSearcher.h core/details/Ukkonen.cpp core/details/Ukkonen.h core/utils/cxxopts.hpp core/StringMatcher.cpp core/StringMatcher.h core/algo/LargeMatcher.cpp core/algo/LargeMatcher.h)

add_library(${LIBNAME} SHARED ${SRCS})