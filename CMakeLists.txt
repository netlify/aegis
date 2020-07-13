cmake_minimum_required(VERSION 3.16)
include(FetchContent)
FetchContent_Declare(cmake GIT_REPOSITORY https://github.com/netlify/cmake)
FetchContent_MakeAvailable(cmake)
set(CMAKE_PROJECT_INCLUDE ${NETLIFY_PROJECT_PRELUDE})
project(aegis LANGUAGES CXX VERSION 0.1.0)

FetchContent_Declare(apex GIT_REPOSITORY git@github.com:netlify/apex.git)
FetchContent_MakeAvailable(apex)

find_package(OpenSSL REQUIRED)

add_library(${PROJECT_NAME})
add_library(netlify::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cxx")
target_sources(${PROJECT_NAME} PRIVATE ${sources})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME}
  PRIVATE
    ${--warn-unused-variable}
    ${--warn-strict-aliasing}
    ${--warn-uninitialized}
    ${--warn-useless-cast}
    ${--warn-cast-align}
    ${--warn-format-2}
    ${--warn-pedantic}
    ${--warn-default}
    ${--warn-extra})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src>)
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    OpenSSL::Crypto
    netlify::apex)

install(TARGETS aegis
  EXPORT netlify-aegis
  ARCHIVE COMPONENT Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT netlify-aegis
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/netlify-aegis
  COMPONENT Development
  NAMESPACE netlify::)
install(DIRECTORY include/
  TYPE INCLUDE
  COMPONENT Development
  FILES_MATCHING
    PATTERN "*.hpp")

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  feature_summary(DEFAULT_DESCRIPTION WHAT ALL)
endif()
