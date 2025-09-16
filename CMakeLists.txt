cmake_minimum_required(VERSION 3.27.6)
project(compute_array_sum VERSION 1.0.0)

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
        EXPORT ${PROJECT_NAME}Targets
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
install(EXPORT ${PROJECT_NAME}Targets 
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/compute_array_sum
)

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/modules/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/<PROJECT-NAME>/<PROJECT-NAME>Config.cmake
#   * <prefix>/lib/cmake/<PROJECT-NAME>/<PROJECT-NAME>ConfigVersion.cmake
#   * <prefix>/lib/cmake/<PROJECT-NAME>/<PROJECT-NAME>Targets.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)