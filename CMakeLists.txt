cmake_minimum_required(VERSION 3.27.6)
project(compute_array_sum)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(compute_array_sum STATIC compute_array_sum/compute_array_sum.cpp)

target_include_directories(compute_array_sum
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)


install(TARGETS compute_array_sum 
        EXPORT compute_array_sumTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY compute_array_sum/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.[ih]*"
)
install(EXPORT compute_array_sumTargets 
        FILE compute_array_sumTargets.cmake
        NAMESPACE compute_array_sum::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/compute_array_sum
)