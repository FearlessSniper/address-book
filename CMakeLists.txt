cmake_minimum_required(VERSION 3.0.0)
project(address-book VERSION 0.1.0)

include(CTest)
enable_testing()

# set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
# Target: cli
# ExternalProject_Add(
#     cli
#     GIT_REPOSITORY https://github.com/daniele77/cli.git
#     GIT_TAG origin/release/v1.2.1
#     )

find_package(nlohmann_json 3.2.0 REQUIRED)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/cli/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

message(STATUS "Building daniele77/cli.")
# Copy the config.json to the build directory
configure_file(config.json . COPYONLY)
add_subdirectory(extern/cli)
add_subdirectory(lib)

add_executable(address-book main.cpp)
target_link_libraries(
    address-book
    PRIVATE lib_address_book
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE cli
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
