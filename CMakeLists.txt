cmake_minimum_required(VERSION 3.10)
project(pfloat)

set(CMAKE_CXX_STANDARD 11)

# ---------------------------------------------------------------------
# Define list of files & directories
message("Project top directory: " ${CMAKE_SOURCE_DIR})
set(pfloatSourceDir
        ${CMAKE_SOURCE_DIR}/src
        )
set(pfloatIncludeDir
        ${CMAKE_SOURCE_DIR}/include
        )

set(sourceFiles
        # Types
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat8high.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat8low.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/upfloat8high.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/upfloat8low.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat8x.cpp

        ${pfloatSourceDir}/pfloat_type_implementations/pfloat16high.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat16low.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/upfloat16high.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/upfloat16low.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat16x.cpp

        ${pfloatSourceDir}/pfloat_type_implementations/pfloat16.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat32.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat64.cpp

        ${pfloatSourceDir}/pfloat_type_implementations/pfloat16d.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat32d.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pfloat64d.cpp

        ${pfloatSourceDir}/pfloat_type_implementations/pfloat.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pdouble.cpp
        ${pfloatSourceDir}/pfloat_type_implementations/pbfloat.cpp

        # Math
        ${pfloatSourceDir}/pfloat_math/pfloat_math_common.cpp
        ${pfloatIncludeDir}/pfloat_math/pfloat_vector_math/pfloat_vector_math.tpp
        ${pfloatIncludeDir}/pfloat_math/pfloat_scalar_math/pfloat_scalar_math.tpp

        # Conversions
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2floatdouble.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2pfloat8high.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2pfloat8low.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2upfloat8high.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2upfloat8low.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2pfloat16high.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2upfloat16high.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2pfloat16low.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2upfloat16low.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2pfloat16.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2pfloat32.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversion2pfloat.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversionhelper_4ranges.cpp
        ${pfloatSourceDir}/pfloat_conversions/pfloat_conversionhelper_16ranges.cpp
        ${pfloatIncludeDir}/pfloat_conversions/pfloat_templated_conversions.tpp
        )

set(includeFiles
        # Top level include
        ${pfloatIncludeDir}/pfloat.h

        # Types
        ${pfloatIncludeDir}/pfloat_types/pfloat_types.h
        ${pfloatIncludeDir}/pfloat_types/pfloat_types_common.h
        ${pfloatIncludeDir}/pfloat_types/pfloat_types_macros.h

        ${pfloatIncludeDir}/pfloat_types/pfloat8high.h
        ${pfloatIncludeDir}/pfloat_types/pfloat8low.h
        ${pfloatIncludeDir}/pfloat_types/upfloat8high.h
        ${pfloatIncludeDir}/pfloat_types/upfloat8low.h
        ${pfloatIncludeDir}/pfloat_types/pfloat8x.h

        ${pfloatIncludeDir}/pfloat_types/pfloat16high.h
        ${pfloatIncludeDir}/pfloat_types/pfloat16low.h
        ${pfloatIncludeDir}/pfloat_types/upfloat16high.h
        ${pfloatIncludeDir}/pfloat_types/upfloat16low.h
        ${pfloatIncludeDir}/pfloat_types/pfloat16x.h

        ${pfloatIncludeDir}/pfloat_types/pfloat16.h
        ${pfloatIncludeDir}/pfloat_types/pfloat32.h
        ${pfloatIncludeDir}/pfloat_types/pfloat64.h

        ${pfloatIncludeDir}/pfloat_types/pfloat16d.h
        ${pfloatIncludeDir}/pfloat_types/pfloat32d.h
        ${pfloatIncludeDir}/pfloat_types/pfloat64d.h

        ${pfloatIncludeDir}/pfloat_types/pfloat.h
        ${pfloatIncludeDir}/pfloat_types/pdouble.h
        ${pfloatIncludeDir}/pfloat_types/pbfloat.h

        # Math
        ${pfloatIncludeDir}/pfloat_math/pfloat_math.h
        ${pfloatIncludeDir}/pfloat_math/pfloat_math_common.h
        ${pfloatIncludeDir}/pfloat_math/pfloat_scalar_math/pfloat_scalar_math.tpp
        ${pfloatIncludeDir}/pfloat_math/pfloat_vector_math/pfloat_vector_math.tpp
        ${pfloatIncludeDir}/pfloat_math/pfloat_matrix_math/pfloat_matrix_math.tpp

        # Conversions
        ${pfloatIncludeDir}/pfloat_conversions/pfloat_conversions.h
        ${pfloatIncludeDir}/pfloat_conversions/pfloat_conversions_common.h
        ${pfloatIncludeDir}/pfloat_conversions/pfloat_conversionhelper_4ranges.h
        ${pfloatIncludeDir}/pfloat_conversions/pfloat_conversionhelper_16ranges.h
        ${pfloatIncludeDir}/pfloat_conversions/pfloat_templated_conversions.tpp
        )

# ---------------------------------------------------------------------
# build the libraries
add_library(pfloat_static STATIC ${sourceFiles} ${includeFiles})
target_include_directories(pfloat_static PUBLIC "${pfloatIncludeDir}")
set_target_properties(pfloat_static  PROPERTIES OUTPUT_NAME pfloat)

add_library(pfloat_shared SHARED ${sourceFiles} ${includeFiles})
target_include_directories(pfloat_shared PUBLIC "${pfloatIncludeDir}")
set_target_properties(pfloat_shared PROPERTIES OUTPUT_NAME pfloat)

# ---------------------------------------------------------------------
# build the test executable
link_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(runtests
        tests/runtests.cpp
        )
target_include_directories(runtests PUBLIC
        "${pfloatIncludeDir}"
        )
message(${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(runtests libpfloat.a)
add_dependencies(runtests pfloat_static pfloat_shared)

# ---------------------------------------------------------------------
# install libraries and runtest executable
set(installTargetDir ${CMAKE_SOURCE_DIR})
install(TARGETS pfloat_shared
        LIBRARY DESTINATION ${installTargetDir}/lib)
install(TARGETS pfloat_static
        ARCHIVE DESTINATION ${installTargetDir}/lib)
install(TARGETS runtests
        RUNTIME DESTINATION ${installTargetDir}/bin)


